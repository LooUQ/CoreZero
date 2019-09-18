/******************************************************************************
*	\file		CoreZero.Network.Sockets.SSLSocket.h
*	\author		Jensen Miller
*	\date		Mar 18, 2019
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
#ifndef COREZERO_NETWORK_SOCKET_SSL_H_
#define COREZERO_NETWORK_SOCKET_SSL_H_

#include "CoreZero.Network.Sockets.TCPSocket.hpp"

namespace CoreZero
{
	namespace Network
	{
		namespace Security
		{
			//class SSLSocket
			//	: public TcpSocket
			//{
			////
			////	Methods
			////
			//public:
			//	//	Inherited via TcpSocket -> I_Socket
			//	virtual int Connect(const IPv4_Address& remoteAddress, uint16_t remotePort) override;
			//	virtual int Listen(const IPv4_Address& localAddress, uint16_t localPort) override;

			//	//	Inherited via TcpSocket -> TStream<>
			//	virtual size_t	Read(uint8_t block[], size_t blocksz) override;
			//	//virtual void	Put(const uint8_t item) override;
			//	//virtual size_t	Write(const uint8_t block[], size_t blocksz) override;
			//	//virtual void	operator<<(const uint8_t block[]) override;
			//	//virtual void	operator<<(const CoreZero::String& data);

			//private:
			//	//ssl_version m_Version;
			//	//ssl_cipher_suite m_CipherSuite;
			//	//ssl_authentication_mode m_AuthMode;
			//	const char* m_CertPath = nullptr;
			//};
		}
	}
}

#endif // !COREZERO_NETWORK_SOCKET_SSL_H_
