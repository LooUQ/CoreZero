/******************************************************************************
*	@file		TCPSocket.hpp
*
*	@author		Jensen Miller
*	@date		Mar 20, 2019
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

#ifndef IOTQ_TCPSOCKET_H
#define IOTQ_TCPSOCKET_H

#include "../Socket.hpp"
#include "../../io/Stream.h"
#include "../../utilities/String.h"


namespace iotq
{
	namespace network
	{
		class TcpSocket
			: public ISocket
			, public streams::TStream<uint8_t>
		{			
		//
		//	Methods
		//
		public:
			//	Inherited via ISocket
			virtual int Connect(const IPv4_Address& remoteAddress, uint16_t remotePort) override;
			virtual int Listen(const IPv4_Address& localAddress, uint16_t localPort) override;

			//	Inherited via TStream<>
			virtual void	Put(const uint8_t item) override;
			virtual size_t	Write(const uint8_t block[], size_t blocksz) override;
			virtual void	operator<<(const uint8_t block[]) override;
			virtual void	operator<<(const iotq::String& data);
		};
	}
}

#endif // !IOTQ_TCPSOCKET_H