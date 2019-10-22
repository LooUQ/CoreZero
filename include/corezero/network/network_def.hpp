/******************************************************************************
*	\file	CoreZero.Network.hpp
*	\author	Jensen Miller
*	\date	Jul 15, 2018
*
*	Copyright (c) 2018 LooUQ Incorporated
*
*	License: The GNU Licence(GNU)
*
*	This file is part of the CoreZero library.
*
*	CoreZero is free software: you can redistribute it and/or modify it under
*	the terms of the GNU General Public License as published by the
*	Free Software Foundation, either version 3 of the License, or (at
*	your option) any later version.
*
*	CoreZero is distributed in the hope that it will be useful, but WITHOUT
*	ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR
*	PURPOSE.  See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public
*	License along with CoreZero.
*	If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/
#ifndef COREZERO_NETWORK_H_
#define COREZERO_NETWORK_H_

#include <stdint.h>

namespace corezero
{
	namespace network
	{
		typedef enum {
			UserDatagram,
			TransmissionControl
		} ProtocolType;


		typedef unsigned int uint;
		typedef struct
		{
			uint sent;		///<	Pings sent.
			uint recvd;		///<	Pings received.
			uint lost;		///<	Pings lost.
			uint min_rtt;	///<	Minimum response time (ms).
			uint max_rtt;	///<	Maximum response time (ms).
			uint avg_rtt;	///<	Average response time (ms).
		} PingSummary;
		
		namespace security
		{
			typedef enum
			{
				SSL3_0 = 0,
				TLS1_0 = 1,
				TLS1_1 = 2,
				TLS1_2 = 3,
				ALL = 4
			} ssl_version;

			typedef enum
			{

				TLS_RSA_WITH_AES_128_CBC_SHA = 0X002F,
				TLS_RSA_WITH_AES_256_CBC_SHA = 0X0035,
				TLS_RSA_WITH_AES_256_CBC_SHA256 = 0X003D,
				TLS_RSA_WITH_RC4_128_SHA = 0X0005,
				TLS_RSA_WITH_RC4_128_MD5 = 0X0005,
				TLS_RSA_WITH_3DES_EDE_CBC_SHA = 0X000A,
				TLS_ECDHE_RSA_WITH_RC4_128_SHA = 0XC011,
				TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA = 0XC012,
				TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA = 0XC013,
				TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA = 0XC014,
				TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256 = 0XC027,
				TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384 = 0XC028,
				TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 = 0XC02F,
				SUPPORT_ALL = 0xFFFF
			} ssl_cipher_suite;

			/// Authentication Mode
			typedef enum
			{
				NO_AUTH,
				MANAGE_SERVER,
				MANAGE_SERVER_AND_CLIENT
			} ssl_authentication_mode;
		}
		typedef enum
		{
			Unspecified,
			IPv4 = 0x2,
			IPv6 = 0xA
		} AddressFamily;

		class IPv4_Address
		{
			static const char format[];
			static const char empty_address[];

		public:
			IPv4_Address();
			IPv4_Address(const IPv4_Address& otherAddress);

			IPv4_Address(const char* address);
			IPv4_Address(uint32_t u32bitval);
			IPv4_Address(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
			~IPv4_Address();

		public:
			const char* c_str() const;
			uint32_t val32() const { return m_Structure.dwordval; }

		private:
			union
			{
				uint32_t dwordval = 0;
				struct
				{
					uint8_t byte0;
					uint8_t byte1;
					uint8_t byte2;
					uint8_t byte3;
				};
			} m_Structure;

			char m_AsString[16];
		};

#ifdef IPV6_SUPPORTED
#define IPV6_ADDRESSING

		class IPv6_Address
		{
			static const char format[];
			static const char empty_address[];

		public:
			IPv6_Address();
			IPv6_Address(const IPv6_Address& otherAddress);

			IPv6_Address(const char* address);
			IPv6_Address(uint64_t globalPrefix, uint16_t subnet, uint64_t interfaceId);
			IPv6_Address(uint16_t byte1
				, uint16_t byte2
				, uint16_t byte3
				, uint16_t byte4
				, uint16_t byte5
				, uint16_t byte6
				, uint16_t byte7
				, uint16_t byte8);
			~IPv6_Address();

		public:
			const char* c_str() const;
			const uint16_t* val128() const { return m_WordArray; }

		private:
			void set_array(uint16_t byte1
				, uint16_t byte2
				, uint16_t byte3
				, uint16_t byte4
				, uint16_t byte5
				, uint16_t byte6
				, uint16_t byte7
				, uint16_t byte8);

		private:
			uint16_t m_WordArray[8];
			char m_AsString[40];
		};

#endif // IPV6_SUPPORTED
	}
}

#endif // !COREZERO_NETWORK_H_