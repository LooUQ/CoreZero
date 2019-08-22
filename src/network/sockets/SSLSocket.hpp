/******************************************************************************
*	@file		SSLSocket.h
*
*	@author		Jensen Miller
*	@date		Mar 18, 2019
*	@copyright	LooUQ Inc 2019
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

#ifndef IOTQ_SSLSOCKET_H
#define IOTQ_SSLSOCKET_H

#include "TCPSocket.hpp"

namespace iotq
{
	namespace network
	{
		namespace security
		{
			class SSLSocket
				: public TcpSocket
			{
			//
			//	Methods
			//
			public:
				//	Inherited via TcpSocket -> ISocket
				virtual int Connect(const IPv4_Address& remoteAddress, uint16_t remotePort) override;
				virtual int Listen(const IPv4_Address& localAddress, uint16_t localPort) override;

				//	Inherited via TcpSocket -> TStream<>
				virtual size_t	Read(uint8_t block[], size_t blocksz) override;
				//virtual void	Put(const uint8_t item) override;
				//virtual size_t	Write(const uint8_t block[], size_t blocksz) override;
				//virtual void	operator<<(const uint8_t block[]) override;
				//virtual void	operator<<(const iotq::String& data);

			private:
				ssl_version m_Version;
				ssl_cipher_suite m_CipherSuite;
				ssl_authentication_mode m_AuthMode;
				const char* m_CertPath = nullptr;
			};
		}
	}
}

#endif // !IOTQ_SSLSOCKET_H
