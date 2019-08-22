#include "Addressing.hpp"

#include <string.h>
#include <stdio.h>

namespace iotq
{
	namespace network
	{

#pragma region IPV4_ADDRESSING

		const char IPv4_Address::format[] = "%u.%u.%u.%u";
		const char IPv4_Address::empty_address[] = "000.000.000.000";

		IPv4_Address::IPv4_Address()
		{
			strncpy(m_AsString, empty_address, 16);
		}

		IPv4_Address::IPv4_Address(const IPv4_Address & otherAddress)
			: m_Structure(otherAddress.m_Structure)
		{
			strncpy(m_AsString, otherAddress.m_AsString, 16);
		}

		IPv4_Address::IPv4_Address(const char * address)
		{
			strncpy(m_AsString, address, 16);
			int b0, b1, b2, b3;
			sscanf(m_AsString, format
				, &b0
				, &b1
				, &b2
				, &b3);
			m_Structure.dwordval = b0 | b1 << 8 | b2 << 16 | b3 << 24;
		}

		IPv4_Address::IPv4_Address(uint32_t u32bitval)
		{
			m_Structure.dwordval = u32bitval;
			sprintf(m_AsString, format
				, m_Structure.byte0
				, m_Structure.byte1
				, m_Structure.byte2
				, m_Structure.byte3);
		}

		IPv4_Address::IPv4_Address(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4)
		{
			m_Structure.byte0 = byte1;
			m_Structure.byte1 = byte2;
			m_Structure.byte2 = byte3;
			m_Structure.byte3 = byte4;
			sprintf(m_AsString, format
				, m_Structure.byte0
				, m_Structure.byte1
				, m_Structure.byte2
				, m_Structure.byte3);
		}

		IPv4_Address::~IPv4_Address()
		{}

		const char * IPv4_Address::c_str() const
		{
			return m_AsString;
		}

#pragma endregion

#pragma region IPV6_ADDRESSING

#ifdef IPV6_ADDRESSING

		const char IPv6_Address::format[] = "%u:%u:%u:%u:%u:%u:%u:%u";
		const char IPv6_Address::empty_address[] = "0000:0000:0000:0000:0000:0000:0000:0000";

		IPv6_Address::IPv6_Address()
		{
			strncpy(m_AsString, empty_address, 40);
		}

		IPv6_Address::IPv6_Address(const IPv6_Address & otherAddress)
		{
			memcpy(m_WordArray, otherAddress.m_WordArray, sizeof(m_WordArray));
			strncpy(m_AsString, otherAddress.m_AsString, 16);
		}

		IPv6_Address::IPv6_Address(const char * address)
		{
			strncpy(m_AsString, address, 16);
			int w1, w2, w3, w4, w5, w6, w7, w8;
			sscanf(m_AsString, format
				, &w1
				, &w2
				, &w3
				, &w4
				, &w5
				, &w6
				, &w7
				, &w8
			);
			set_array(w1, w2, w3, w4, w5, w6, w7, w8);
		}

		IPv6_Address::IPv6_Address(uint64_t globalPrefix, uint16_t subnet, uint64_t interfaceId)
		{
		}

		IPv6_Address::IPv6_Address(uint16_t byte1, uint16_t byte2, uint16_t byte3, uint16_t byte4, uint16_t byte5, uint16_t byte6, uint16_t byte7, uint16_t byte8)
		{
			set_array(byte1, byte2, byte3, byte4, byte5, byte6, byte7, byte8);
			sprintf(m_AsString, format
			, m_WordArray[0]
			, m_WordArray[1]
			, m_WordArray[2]
			, m_WordArray[3]
			, m_WordArray[4]
			, m_WordArray[5]
			, m_WordArray[6]
			, m_WordArray[7]
			);
		}

		IPv6_Address::~IPv6_Address()
		{
		}

		const char * IPv6_Address::c_str() const
		{
			return m_AsString;
		}

		void IPv6_Address::set_array(uint16_t byte1, uint16_t byte2, uint16_t byte3, uint16_t byte4, uint16_t byte5, uint16_t byte6, uint16_t byte7, uint16_t byte8)
		{
			m_WordArray[0] = byte1;
			m_WordArray[1] = byte2;
			m_WordArray[2] = byte3;
			m_WordArray[3] = byte4;
			m_WordArray[4] = byte5;
			m_WordArray[5] = byte6;
			m_WordArray[6] = byte7;
			m_WordArray[7] = byte8;
		}
#endif
#pragma endregion

	}
}

