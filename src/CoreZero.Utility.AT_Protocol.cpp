//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include "CoreZero.Utility.AT_Protocol.hpp"

#define LF	'\n'
#define CR	'\r'



namespace CoreZero
{
	namespace Utility
	{
		/**********************************************************************
		 *	\brief Destructor.
		 */
		AT_Protocol<false>::~AT_Protocol()
		{
			//	Delete buffer.
			delete[] m_buffer;
			delete m_bg96;
			delete &CSerialController::GetDefaultController();
		}

		void AT_Protocol<false>::Initialize()
		{
			m_bg96 = CSerialController::GetDefaultController().OpenPort(PortName, 115200);
			m_bg96->ReceivedData += CoreZero::Create_MemberDelegate(this, &AT_Protocol<false>::dispatch_incoming);

			m_buffer = new char[AT_MaxCommandLen];
			strncpy(m_buffer, AT_Header, sizeof(AT_Header));
			m_bufSize = 2;

			SendCommand("E0");
			SendCommand("V0");
		}



		/**********************************************************************
		 *	\brief Send a command without any arguments.
		 *
		 *	\param[in] cmd The AT command to send.
		 *	\returns The command's result code.
		 */
		int AT_Protocol<false>::SendCommand(const char cmd[])
		{
			int result = -1;

			strcat(m_buffer, cmd);
			m_bufSize += strlen(cmd);

			m_awaitingResponse = true;
			send_command();
			await_result();			

			result = m_recentResult;
			m_recentResult = -1;

			return result;
		}



		/**********************************************************************
		 *	\brief Send a formated command including its arguments.
		 *
		 *	\param[in] format The format of the command and its arguments.
		 *	\param[in] ... The arguments.
		 *	\returns The command's result code.
		 */
		int AT_Protocol<false>::SendCommandF(const char format[], ...)
		{
			int result = -1;

			va_list cmd_args;
			va_start(cmd_args, format);
			m_bufSize += vsprintf(m_buffer + m_bufSize, format, cmd_args);
			va_end(cmd_args);

			m_awaitingResponse = true;
			send_command();
			await_result();

			result = m_recentResult;
			m_recentResult = -1;

			return result;
		}

		void AT_Protocol<false>::poll()
		{
			m_bg96->GetAvailable();
		}

		/**********************************************************************
		 *	\brief Send the buffer holding the command.
		 */
		void AT_Protocol<false>::send_command()
		{
			m_buffer[m_bufSize++] = CR;
			m_bg96->Write(m_buffer, m_bufSize);
			m_buffer[sizeof(AT_Header) - 1] = NULL;
			m_bufSize = sizeof(AT_Header) - 1;
		}



		/**********************************************************************
		 *	\brief Await the response result.
		 */
		void AT_Protocol<false>::await_result()
		{
			while (m_awaitingResponse)
			{
				m_bg96->GetAvailable();
			}
		}



		/**********************************************************************
		 *	\brief Handle incoming data.
		 *
		 *	\param[in] inData The incoming data.
		 */
		void AT_Protocol<false>::dispatch_incoming(const char* inData)
		{	//ASSUMPTION: inData is a full response.
			size_t data_len = strlen(inData);

			//	determine whether data was expected for an immediate reponse,
			//		or if the data is out of band.
			if (m_awaitingResponse)
			{
				//	check result code at the end
				const char* data_end = inData + data_len - 2;
				if (isdigit(*data_end)) {
					m_recentResult = *data_end - '0';
					//	check for a response for results
					if (m_responseLocation != nullptr)
					{
						// copy the response
						strncpy(*m_responseLocation, inData, data_len - 2);
						(*m_responseLocation)[data_len - 2] = '\0';
					}
				}
				m_awaitingResponse = false;
			}
			else {
				m_recentResult = -1;
				process_out_of_band_data(inData);
			}
		}

		void AT_Protocol<false>::process_out_of_band_data(const char* inData)
		{

		}
	}
}