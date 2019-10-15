//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include <gtest/gtest.h>

#include <string>
#include <thread>
using namespace std::chrono_literals;

//#include <Win32.Devices.SerialDevice.h>
constexpr const uint16_t PortNumber = 12;

#include <CoreZero.Utility.ATProtocol.hpp>



namespace CoreZero
{
	namespace Utility
	{
		namespace tests
		{
			class ATProtocolTest
				: public ::testing::Test
			{
			protected:

			};

			TEST_F(ATProtocolTest, ConstructNull)
			{
				ATProtocol<false> at = nullptr;
			}
		}
	}



	//TEST_CLASS(AT_Protocol_tests)
	//{	
	//	Win32::Devices::SerialDevice m_serialDevice = nullptr;
	//	ATProtocol<false> protocol = nullptr;



	//	size_t write(const char* _out, size_t size)
	//	{
	//		m_serialDevice.Write(std::string(_out, size));
	//		return size;
	//	}

	//	void handle_rx(std::string inStr)
	//	{			
	//		protocol.Parse(inStr.c_str(), inStr.length());
	//	}

	//public:
	//	TEST_METHOD(construct_blank)
	//	{

	//	}

	//	TEST_METHOD(construct_runtime)
	//	{
	//		m_serialDevice = Win32::Devices::SerialDevice::FromPortNumber(PortNumber);
	//		m_serialDevice.BaudRate(115200);

	//		m_serialDevice.UsingEvents(true);
	//		m_serialDevice.ReceivedData += Create_MemberDelegate(this, &AT_Protocol_tests::handle_rx);


	//		protocol = ATProtocol<false>( Create_MemberDelegate(this, &AT_Protocol_tests::write) );

	//		unsigned rssi = 99;
	//		AT_Command<unsigned> SignalQualityReport("+CSQ");
	//		if (protocol.SendCommand(SignalQualityReport) == AT_OK)
	//		{
	//			SignalQualityReport.Get(true, rssi);
	//		}

	//		m_serialDevice.Defer(1000ms);
	//	}



	//	TEST_METHOD(run_sample_setup)
	//	{
	//		m_serialDevice = Win32::Devices::SerialDevice::FromPortNumber(PortNumber);
	//		m_serialDevice.BaudRate(115200);

	//		m_serialDevice.UsingEvents(true);
	//		m_serialDevice.ReceivedData += Create_MemberDelegate(this, &AT_Protocol_tests::handle_rx);


	//		protocol = ATProtocol<false>(Create_MemberDelegate(this, &AT_Protocol_tests::write));

	//		Logger::WriteMessage("Manufacturer: ");

	//		CoreZero::String manufacturer_id;
	//		AT_Command<CoreZero::String> ManufacturerIdRequest("+CGMI");
	//		if (protocol.SendCommand(ManufacturerIdRequest) == AT_OK)
	//		{
	//			manufacturer_id.reserve(32);
	//			ManufacturerIdRequest.Get(false, manufacturer_id);
	//		}
	//		Logger::WriteMessage(manufacturer_id.c_str());
	//		Assert::IsTrue(manufacturer_id.GetLength() > 0);

	//		Logger::WriteMessage("\nModel: ");

	//		CoreZero::String model_id;
	//		AT_Command<CoreZero::String> ModelIdRequest("+CGMM");
	//		if (protocol.SendCommand(ModelIdRequest) == AT_OK)
	//		{
	//			model_id.reserve(8);
	//			ModelIdRequest.Get(false, model_id);
	//		}

	//		Logger::WriteMessage(model_id.c_str());
	//		Assert::IsTrue(model_id.GetLength() > 0);

	//		Logger::WriteMessage("\nRevision: ");

	//		CoreZero::String firmware_revision;
	//		AT_Command<CoreZero::String> RevisionIdRequest("+CGMR");
	//		if (protocol.SendCommand(RevisionIdRequest) == AT_OK)
	//		{
	//			firmware_revision.reserve(32);
	//			RevisionIdRequest.Get(false, firmware_revision);
	//		}
	//		Logger::WriteMessage(firmware_revision.c_str());
	//		Assert::IsTrue(firmware_revision.GetLength() > 0);


	//		m_serialDevice.Defer(1000ms);
	//	}

	//	TEST_METHOD(using_async_commands)
	//	{
	//		//m_serialDevice = Win32::Devices::SerialDevice::FromPortNumber(PortNumber);
	//		//m_serialDevice.BaudRate(115200);
	//		//m_serialDevice.UsingEvents(true);
	//		//m_serialDevice.ReceivedData += Create_MemberDelegate(this, &AT_Protocol_tests::handle_rx);
	//		//protocol = ATProtocol<false>(Create_MemberDelegate(this, &AT_Protocol_tests::write));

	//		////	Open a socket asynchronously
	//		//typedef struct Socket
	//		//{
	//		//	unsigned connect_id;
	//		//} Socket;

	//		//AT_Command<unsigned, unsigned> OpenSocketRequest("+QIOPEN", 1, 0, "UDP", "127.0.0.1", 8080, 0, 1);
	//		//if (!protocol.SendCommand(OpenSocketRequest) == AT_OK)
	//		//{
	//		//	//	[error]: command was ill-formed.
	//		//}
	//		//OpenSocketRequest.GetAsync(
	//		//	[](unsigned connectID, unsigned err)
	//		//	{
	//		//		Socket* _sock = new Socket{ connectID };
	//		//	}
	//		//);
	//	}
	//};
}