#ifndef IOTQ_ATPROTOCOL_H
#define IOTQ_ATPROTOCOL_H


#include "Stream.h"
#include "../framework/Event.h"
#include "../framework/AsyncHandle.h"
#include "../containers/Vector.h"
#include "../utilities/String.h"
#include <stdint.h>

#define ASCII_T char


#define	COMMAND_ACK				0
#define DCE_DATA_MODE			1
#define DCE_CALL_DETECTED		2
#define NO_CARRIER				3
#define AT_ERROR				4
#define	NO_DIALTONE_DETECTED	6
#define BUSY_SIGNAL_DETECTED	7
#define NO_ANSWER_DETECTED		8

namespace iotq
{
	namespace io
	{		
		namespace protocols
		{
			delegate_t <const char[], size_t> OnOOBData;
			delegate_t <const char[], size_t> CommandHandler;
			
			using framework::Event;
			using SmartCallback = memory::SmartPointer<iotq::utilities::VoidFunctor<String>>;

			class ATProtocol final
				: public streams::TStream<>
			{
				struct OOBDataExpectation
				{
					SmartCallback handler;
					const char* prefix;					
				};

			public:
				ATProtocol() : m_ResponseStream(new streams::TStream<>) {}
				virtual ~ATProtocol();

			//
			//	Methods
			//
			public:
				int SendCommand(const char command[]);
				int SendCommand(const char command[], size_t commandLength);
				int SendCommandF(const char format[], ...);				

				int	LookFor(const char* atResponse, size_t len);

				template <typename VOID_LAMBDA>
				bool	SubscribeToPrefix(const char prefix[], VOID_LAMBDA voidCallback);
				bool	UnsubscribePrefix(const char prefix[]);
				bool	ProcessOutOfBandData();

				size_t	GetSome(char block[], size_t blocksz);
				void Flush() override;


			//
			//	Getters and Setters
			//
			public:
				int		GetResults(const char* format, ...);
				String	GetLine();
				void	SetCommandHandler(iotq::utilities::VoidFunctor<const char[], size_t>* commandHandler);

			private:
				void await_response(int& result);

			public:
				void SetTimeout(uint32_t timeout) { m_Timeout = timeout; }
				uint32_t GetTimeout() const { return m_Timeout; }

			public:
				Event<OnOOBData> OutOfBandDataReceived;				

			private:
				uint32_t m_Timeout = 5000;

				String m_RecentSearch;

				iotq::containers::Vector<OOBDataExpectation> m_Expectations;

				CommandHandler* send_command;

				iotq::streams::TStream<>* m_ResponseStream;
			};


			template<typename VOID_LAMBDA>
			inline bool ATProtocol::SubscribeToPrefix(const char prefix[], VOID_LAMBDA voidCallback)
			{
				// Check if prefix is already in vector

				// Create a new expectation
				OOBDataExpectation new_expectation;
				new_expectation.prefix = prefix;
				new_expectation.handler = new iotq::utilities::VoidFunctor<VOID_LAMBDA, iotq::utilities::VoidFunctor<String>>(
					new VOID_LAMBDA(voidCallback), (void(VOID_LAMBDA::*)(String)) & VOID_LAMBDA::operator()
					);
				m_Expectations.PushBack(new_expectation);
				return true;
			}
		}
	}
}


#endif // !IOTQ_ATPROTOCOL_H