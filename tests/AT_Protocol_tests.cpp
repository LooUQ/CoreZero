//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <string>
#include <thread>

#include <Win32.Devices.SerialDevice.h>
constexpr const uint16_t PortNumber = 10;

#include <CoreZero.Utility.AT_Protocol.hpp>
using namespace CoreZero::Utility;



namespace CoreZero
{
	TEST_CLASS(AT_Protocol_tests)
	{	
		Win32::Devices::SerialDevice m_serialDevice = nullptr;

		unsigned write(const char _out[], unsigned size)
		{
			m_serialDevice.Write(std::string(_out, size));
			return 0U;
		}

		unsigned read(char _in[], unsigned size)
		{
			std::string in_str;
			m_serialDevice.Read(in_str);
			strcpy(_in, in_str.c_str());
			return 0U;
		}

	public:
		TEST_METHOD(construct_blank)
		{
			AT_Protocol<false> at = nullptr;
		}

		TEST_METHOD(construct_runtime)
		{
			m_serialDevice = Win32::Devices::SerialDevice::FromPortNumber(PortNumber);
			AT_Protocol<false> at = {
				Create_MemberDelegate(this, &AT_Protocol_tests::write),
				Create_MemberDelegate(this, &AT_Protocol_tests::read)
			};
		}
	};
}