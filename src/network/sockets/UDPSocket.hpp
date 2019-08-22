/******************************************************************************
*	@file		UDPSocket.hpp
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

#ifndef IOTQ_UDPSOCKET_H
#define IOTQ_UDPSOCKET_H

#include "../Socket.hpp"

namespace iotq
{
	namespace network
	{
		class UdpSocket
			: public ISocket
		{
		//
		//	Methods
		//
		public:
			virtual size_t SendTo(const uint8_t data[], size_t sendLength, IPv4_Address remoteAddress, uint16_t remotePort);

			// Inherited via ISocket
			virtual int	Connect(const IPv4_Address & remoteAddress, uint16_t remotePort) override;
			virtual int	Listen(const IPv4_Address & localEndPoint, uint16_t localPort) override;
			virtual size_t	Send(const uint8_t data[], size_t toSend) override;
			virtual size_t	SendFile(FILE * fileToSend, fpos_t * filePos = NULL) override;
		};
	}
}

#endif // !IOTQ_UDPSOCKET_H