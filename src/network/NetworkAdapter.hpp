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

#ifndef IOTQ_INETWORKADAPTER_H
#define IOTQ_INETWORKADAPTER_H

#include "../framework/AsyncHandle.h"
#include "../framework/Event.h"

#include <stdint.h>
#include <stdio.h>

#ifdef NETWORKADAPTER_SUPPORTS_IPV6
#define IPV6_SUPPORTED
#endif

constexpr int NETWORK_NO_SSL_SUPPORT = 0x0;
constexpr int NETWORK_SUPPORTS_SSL = 0x1;

#include "Addressing.hpp"

namespace iotq
{
	namespace network
	{
		typedef enum {
			BufferAccess,
			DirectPush,
			Transparent
		} DataMode;


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

//#ifdef NETWORKADAPTER_SUPPORTS_SSL
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
//#endif // !NETWORKADAPTER_SUPPORTS_SSL


		//typedef enum {
		//	Ethernet = 0x6,
		//	GenericModem = 48,
		//	Wireless80211 = 71,
		//	Wwanpp = 243,
		//	Wwanpp2 = 244
		//} NetworkInterfaceType;

		delegate_t <void*, size_t>	OnDataReceived;

		class INetworkAdapter
		{
		//
		//	Methods
		//
		public:
			void SetAsDefault();
			static INetworkAdapter * GetDefault();

		public:
			virtual PingSummary	Ping(const IPv4_Address& ipAddress, unsigned int timeout = 4000, unsigned int pingNum = 4) = 0;
			virtual PingSummary	Ping(const char hostName[], unsigned int timeout = 4000, unsigned int pingNum = 4) = 0;
			virtual IPv4_Address HostByName(const char* hostName) = 0;

			virtual int Connect(int &connectionId, uint32_t connectionFlags, IPv4_Address remoteAddress, uint16_t remotePort) = 0;
			virtual int ConnectSSL(int &connectionId, uint32_t connectionFlags, uint32_t securityFlags, IPv4_Address remoteAddress, uint16_t remotePort) = 0;			
			virtual int Listen(int &connectionId, uint32_t connecitonFlags, IPv4_Address localAddress, uint16_t localPort) = 0;
			virtual int Disconnect(int connectionId, int timeout = 0) = 0;

			virtual size_t Send(int connectionId, const uint8_t data[], size_t dataLength) = 0;
			virtual size_t SendTo(int connectId, const uint8_t data[], size_t dataLength, const IPv4_Address& remoteAddress, uint16_t remotePort) = 0;
			virtual size_t SendFile(int connectionId, FILE* fileToSend, fpos_t* filePos = NULL) = 0;
			virtual size_t Receive(int connectionId, uint8_t data[], size_t dataLength) = 0;
			virtual size_t ReceiveFrom(int connectionId, uint8_t data[], size_t dataLength, const IPv4_Address& remoteAddress, uint16_t remotePort) = 0;

			virtual int	ConfigureOptions(int connectionId, int options) = 0;
			virtual bool IsNetworkAvailable() = 0;
			virtual const char* GetNetworkInterfaceType() = 0;
		};
	}
}

#endif // !IOTQ_INETWORKADAPTER_H
