/******************************************************************************
*	@file		INetworkAdapter.h
*
*	@author		Jensen Miller
*	@date		Jul 15, 2018
*	@copyright	LooUQ Inc 2018
*
*	@details
*
*	License:
*		The GNU Licence(GNU)
*
*	This file is part of the iotq library.
*
*	IotQc is free software: you can redistribute it and/or modify it under
*	the terms of the GNU General Public License as published by the
*	Free Software Foundation, either version 3 of the License, or (at
*	your option) any later version.
*
*	IotQc is distributed in the hope that it will be useful, but WITHOUT
*	ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR
*	PURPOSE.  See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public
*	License along with iotq.
*	If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/
#pragma once

#ifndef IOTQ_ADDRESSING_H
#define IOTQ_ADDRESSING_H

#include <stdint.h>

namespace iotq
{
	namespace network
	{
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

#endif // !IOTQ_ADDRESSING_H