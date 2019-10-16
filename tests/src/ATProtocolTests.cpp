//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include <gtest/gtest.h>
#include <corezero/utility/atprotocol.hpp>

#include <Win32.Devices.SerialDevice.h>
constexpr const uint16_t PortNumber = 12;

#include <string>
#include <thread>
using namespace std::chrono_literals;



//	Aliases for Google Tests <-> Microsoft UnitTest Framework
namespace Assert
{
	template <typename T>
	inline void AreEqual(T val1, T val2)
	{
		ASSERT_EQ(val1, val2);
	}

	inline void IsTrue(bool _expectedTrue)
	{
		ASSERT_TRUE(_expectedTrue);
	}
}

class Logger
{
public:
	static void WriteMessage(const char* const message)
	{
		std::cerr << message << std::endl;
	}
};

namespace corezero
{
	namespace utility
	{
		namespace tests
		{
			class ATProtocolTest
				: public ::testing::Test
			{
			protected:
				virtual void SetUp() override
				{
					m_serialDevice = Win32::Devices::SerialDevice::FromPortNumber(PortNumber);
					m_serialDevice.BaudRate(115200);
				}

				virtual void TearDown() override
				{
					m_serialDevice.Close();
				}

				ATProtocol<false> m_protocol = nullptr;

				Win32::Devices::SerialDevice m_serialDevice = nullptr;

			public:
				size_t write(const char* _out, size_t size)
				{
					m_serialDevice.Write(std::string(_out, size));
					return size;
				}

				void handle_rx(std::string inStr)
				{
					m_protocol.Parse(inStr.c_str(), inStr.length());
				}
			};



			TEST_F(ATProtocolTest, ConstructNull)
			{
				// the null instance was constructed in SetUp()
				SUCCEED();
			}



			TEST_F(ATProtocolTest, EventDrivenTest)
			{
				m_serialDevice.UsingEvents(true);
				m_serialDevice.ReceivedData += Create_MemberDelegate(
					(ATProtocolTest* const)this, &ATProtocolTest::handle_rx
				);

				m_protocol = ATProtocol<false>(Create_MemberDelegate(
					(ATProtocolTest* const)this, &ATProtocolTest::write
				));

				unsigned rssi = 99;
				ATCommand<unsigned> SignalQualityReport("+CSQ");
				if (m_protocol.SendCommand(SignalQualityReport) == ATResponseCode<false>::atOk)
				{
					SignalQualityReport.Get(true, rssi);
				}

				m_serialDevice.Defer(1000ms);
			}

			TEST_F(ATProtocolTest, SampleOperation)
			{
				m_serialDevice.UsingEvents(true);
				m_serialDevice.ReceivedData += Create_MemberDelegate(
					(ATProtocolTest* const)this, &ATProtocolTest::handle_rx
				);


				m_protocol = ATProtocol<false>(Create_MemberDelegate(
					(ATProtocolTest* const)this, &ATProtocolTest::write
				));

				Logger::WriteMessage("Manufacturer: ");

				CoreZero::String manufacturer_id;
				ATCommand<CoreZero::String> ManufacturerIdRequest("+CGMI");
				if (m_protocol.SendCommand(ManufacturerIdRequest) == ATResponseCode<false>::atOk)
				{
					manufacturer_id.reserve(32);
					ManufacturerIdRequest.Get(false, manufacturer_id);
				}
				Logger::WriteMessage(manufacturer_id.c_str());
				Assert::IsTrue(manufacturer_id.GetLength() > 0);

				Logger::WriteMessage("\nModel: ");

				CoreZero::String model_id;
				ATCommand<CoreZero::String> ModelIdRequest("+CGMM");
				if (m_protocol.SendCommand(ModelIdRequest) == ATResponseCode<false>::atOk)
				{
					model_id.reserve(8);
					ModelIdRequest.Get(false, model_id);
				}

				Logger::WriteMessage(model_id.c_str());
				Assert::IsTrue(model_id.GetLength() > 0);

				Logger::WriteMessage("\nRevision: ");

				CoreZero::String firmware_revision;
				ATCommand<CoreZero::String> RevisionIdRequest("+CGMR");
				if (m_protocol.SendCommand(RevisionIdRequest) == ATResponseCode<false>::atOk)
				{
					firmware_revision.reserve(32);
					RevisionIdRequest.Get(false, firmware_revision);
				}
				Logger::WriteMessage(firmware_revision.c_str());
				Assert::IsTrue(firmware_revision.GetLength() > 0);


				m_serialDevice.Defer(1000ms);
			}

			TEST_F(ATProtocolTest, AsyncTest)
			{
				m_serialDevice.UsingEvents(true);
				m_serialDevice.ReceivedData += Create_MemberDelegate(
					(ATProtocolTest * const)this, &ATProtocolTest::handle_rx
				);

				m_protocol = ATProtocol<false>(Create_MemberDelegate(
					(ATProtocolTest * const)this, &ATProtocolTest::write
				));

				//	Open a socket asynchronously
				typedef struct Socket
				{
					unsigned connect_id;
				} Socket;

				ATCommand<unsigned, unsigned> OpenSocketRequest("+QIOPEN", 1, 0, "UDP", "127.0.0.1", 8080, 0, 1);
				if (!m_protocol.SendCommand(OpenSocketRequest) == ATResponseCode<false>::atOk)
				{
					//	[error]: command was ill-formed.
				}
				OpenSocketRequest.GetAsync(
					[](unsigned connectID, unsigned err)
					{
						Socket* _sock = new Socket{ connectID };
					}
				);
			}
		}
	}
}