/******************************************************************************
*	\file	CoreZero.Network.Sockets.UDPSocket.hpp
*	\author	Jensen Miller
*	\date	Mar 20, 2019
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
#ifndef COREZERO_NETWORK_SOCKET_UDP_H_
#define COREZERO_NETWORK_SOCKET_UDP_H_

#include "CoreZero.Network.Sockets.hpp"

namespace CoreZero
{
	namespace Network
	{
		namespace Sockets
		{
			class UdpSocket
				: public I_Socket
			{
				//
				//	Methods
				//
			public:
				virtual size_t SendTo(const uint8_t data[], size_t sendLength, IPv4_Address remoteAddress, uint16_t remotePort);

				// Inherited via I_Socket
				virtual int	Connect(const IPv4_Address& remoteAddress, uint16_t remotePort) override;
				virtual int	Listen(const IPv4_Address& localEndPoint, uint16_t localPort) override;
				virtual size_t	Send(const uint8_t data[], size_t toSend) override;
				virtual size_t	SendFile(FILE* fileToSend, fpos_t* filePos = NULL) override;
			};
		}
	}
}

#endif // !COREZERO_NETWORK_SOCKET_UDP_H_