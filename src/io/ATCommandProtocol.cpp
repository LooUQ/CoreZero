#include "ATCommandProtocol.hpp"

#include <stdarg.h>
#include <ctype.h>
#include <assert.h>

#define CR	'\r'
#define LF	'\n'
#define AT	"AT"
#define SEND_COMMAND (*send_command)



namespace iotq {

	template <int (*StartToResult)(int) = isdigit, char AcceptOn = CR>
	class AT_DFA
	{		
		enum State
		{
			StartLine,
			ResultCode,
			Response,
			Accept
		};

		int		m_Result = 4;
		State	m_State = StartLine;
		char	m_Buffer[0x40];
		int		m_Pos = 0;

	public:
		AT_DFA() { memset(m_Buffer, NULL, 0x40); }

		bool Process(const unsigned char& in) {
			m_Buffer[m_Pos++] = in;
			assert(m_Pos <= 64);

			switch (m_State)
			{
			case StartLine:
				if (iscntrl(in)) {
					break;
				} else if (StartToResult(in)) {
					m_State = ResultCode;
				} else {
					m_State = Response;
				}
				break;

			case ResultCode:
				if (in == AcceptOn) {
					m_Result = m_Buffer[--m_Pos-1] - 0x30;
					memset(&m_Buffer[--m_Pos], NULL, 2);
					m_State = Accept;
				} else {
					m_State = Response;
				}
				break;

			case Response:
				if (in == CR) {
					m_State = StartLine;
				}
				break;

			case Accept:
				// If anything arrives after being accepted
				m_State = StartLine;
				break;
			}

			return (m_State == Accept);
		}

		size_t DumpResponses(streams::TStream<> * responseStream) {
			return responseStream->Write(m_Buffer, m_Pos);
		}

		int GetResult() const {
			return m_Result;
		}
	};

	namespace io {
		namespace protocols {

			/** Destructor */
			ATProtocol::~ATProtocol()
			{
				delete m_ResponseStream;
			}



			/**
			 *	@brief Send an AT command.
			 *	
			 *	@param[in] command The command to send. (Null-terminated)
			 *	@returns A result code.
			 */
			int ATProtocol::SendCommand(const char command[])
			{
				return SendCommand(command, strlen(command));
			}



			/**
			 *	@brief Send an AT command of specific length.
			 *
			 *	@param[in] commandLength The length of the command to send.
			 *	@returns A result code.
			 */
			int ATProtocol::SendCommand(const char command[], size_t commandLength)
			{
				int result;

				char* command_buffer = new char[commandLength + 4];
				strncpy(command_buffer, AT, 2);
				strcpy(command_buffer+2, (const char*)command);
				strcat(command_buffer, "\r");

				SEND_COMMAND(command_buffer, commandLength + 3);
				delete[] command_buffer;

				await_response(result);

				return result;
			}



			/**
			 *	@brief Send a formated AT command. Variable arguments.
			 *	
			 *	@param[in] format The format string to input variable arguments.
			 *	@param[in] ... The arguments to fill the formated command with.
			 *	@returns A result code.
			 */
			int ATProtocol::SendCommandF(const char format[], ...)
			{
				int result;

				char* command_buffer = new char[0x80];
				strncpy(command_buffer, AT, 2);

				va_list command_arguments;
				va_start(command_arguments, format);
				size_t command_length = vsprintf(command_buffer+2, format, command_arguments);
				va_end(command_arguments);

				command_buffer[command_length + 2] = CR;
				command_buffer[command_length + 3] = NULL;

				SEND_COMMAND(command_buffer, command_length + 3);
				delete[] command_buffer;

				await_response(result);

				return result;
			}



			/**
			 *	@brief Looks for a specified response.
			 *	
			 *	@param[in] atResponse The prefix of the AT response to look for.
			 *	@param[in] len The number of characters to compare.
			 *	@returns Whether the response was found.
			 */
			int ATProtocol::LookFor(const char* atResponse, size_t len)
			{
				int result = -1;

				// New search, delete past if neccessary				
				m_RecentSearch.Clear();
				m_RecentSearch = GetLine();
				result = m_RecentSearch.Compare(0, len, atResponse);

				if (result != 0) {
					m_RecentSearch.Clear();
				}
				return result;
			}



			/**
			 *	@brief Unsubscribe to a prefix that is linked to a pending callback
			 *
			 *	@param[in] prefix The prefix to remove.
			 *	@returns Whether the prefix was present to be removed.
			 */
			bool ATProtocol::UnsubscribePrefix(const char prefix[])
			{
				for (int expected = 0; expected < m_Expectations.GetSize(); expected++)
				{
					if (strncmp(m_Expectations[expected].prefix, prefix, strlen(prefix)) == 0)
					{
						m_Expectations.erase(m_Expectations.begin() + expected);
						return true;
					}
				}
				return false;
			}



			/**
			 *	@brief Process data that arrived out-of-band (unexpected).
			 *
			 *	@returns Whether there was data to process.
			 */
			bool ATProtocol::ProcessOutOfBandData()
			{
				bool result = false;
				if (!AvailableForRead()) {
					return result;
				}
				else
				{
					char* line; size_t line_len;
					while (line_len = ReadUntil(LF))
					{
						bool handled = false;
						line = new char[line_len+1];
						(*this) >> line;
						line[line_len] = NULL;

						for (auto expected : m_Expectations)
						{
							if (strncmp(expected.prefix, line, strlen(expected.prefix)) == 0)
							{
								(*expected.handler)(String(line, line_len));
								handled = true;
								break;
							}
						}
						if (!handled) {
							OutOfBandDataReceived(line, line_len);
						}
						delete[] line;
						result = true;
					}
					return result;
				}
			}



			/**
			 *	@brief Get some data from the response stream.
			 *
			 *	@param[out] block A block of data requested from the response stream.
			 *	@param[in] blocksz The size of the block.
			 *	@returns The amount of data actually retrieved.
			 */
			size_t ATProtocol::GetSome(char block[], size_t blocksz)
			{
				return m_ResponseStream->Read(block, blocksz);
			}



			/**
			 *	@brief Flush the stream.
			 */
			void ATProtocol::Flush()
			{
				Seek(-1);
				m_ResponseStream->Seek(-1);
			}


			/**
			 *	@brief Get the results of the searched for response.
			 *
			 *	@param[in] format The format of the response containing the results.
			 *	@param[out] ... The results to set.
			 *	@returns The number of results parsed.
			 */
			int ATProtocol::GetResults(const char* format, ...)
			{
				int results_parsed;
				va_list results_to_match;
				va_start(results_to_match, format);

				// Check to see if the response was already looked for
				String recent_response;
				if (m_RecentSearch.IsEmpty()) {
					recent_response = GetLine();
				}
				else
				{
					recent_response = m_RecentSearch;
					m_RecentSearch.Clear();
				}

				results_parsed = vsscanf(recent_response.c_str(), format, results_to_match);				
				va_end(results_to_match);
				return results_parsed;
			}



			/**
			 *	@brief Get a line of response from the response stream.
			 *
			 *	@returns A string containing the line.
			 */
			String ATProtocol::GetLine()
			{
				String line;
				size_t lineLength = m_ResponseStream->ReadUntil(LF);
				if (lineLength) {
					char* responseLine = new char[lineLength + 1];
					m_ResponseStream->Read(responseLine, lineLength);
					line = String(responseLine, lineLength);
					delete[] responseLine;
				}
				return line;
			}



			/**
			 *	@brief Set the handler that will forward commands to the device.
			 *
			 *	@param[in] commandHandler The command handler.
			 */
			void ATProtocol::SetCommandHandler(iotq::utilities::VoidFunctor<const char[], size_t>* commandHandler)
			{
				send_command = commandHandler;
			}


			/**
			 *	@brief Await a response to a sent command.
			 *
			 *	@param[in/out] result The result of the command.
			 */
			void ATProtocol::await_response(int& result)
			{
				AT_DFA<> dfa;

				for(;;)
				{
					if (AvailableForRead())
					{
						if (dfa.Process(Get()))
						{
							dfa.DumpResponses(m_ResponseStream);
							result = dfa.GetResult();
							break;
						}
					}
				}
			}
		}
	}
}