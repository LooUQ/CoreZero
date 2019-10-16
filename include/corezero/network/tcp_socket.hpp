/******************************************************************************
*	\file	CoreZero.Network.Sockets.TCPSocket.hpp
*
*	\author	Jensen Miller
*	\date		Mar 20, 2019
*
*	Copyright (c) 2019 LooUQ Incorporated
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
#ifndef COREZERO_NETWORK_SOCKET_TCP_H_
#define COREZERO_NETWORK_SOCKET_TCP_H_

#include "sockets.hpp"
#include "../streams/streams.hpp"
#include "../string.hpp"


namespace corezero
{
	namespace network
	{
		//class TcpSocket
		//	: public I_Socket
		//	, public Streams::Stream<uint8_t>
		//{			
		////
		////	Methods
		////
		//public:
		//	//	Inherited via I_Socket
		//	virtual int Connect(const IPv4_Address& remoteAddress, uint16_t remotePort) override;
		//	virtual int Listen(const IPv4_Address& localAddress, uint16_t localPort) override;

		//	//	Inherited via TStream<>
		//	virtual void	Put(const uint8_t item) override;
		//	virtual size_t	Write(const uint8_t block[], size_t blocksz) override;
		//	virtual void	operator<<(const uint8_t block[]) override;
		//	virtual void	operator<<(const CoreZero::String& data);
		//};
	}
}

#endif // !COREZERO_NETWORK_SOCKET_TCP_H_