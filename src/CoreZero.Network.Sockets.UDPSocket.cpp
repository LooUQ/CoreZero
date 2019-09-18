//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include "CoreZero.Network.Sockets.UDPSocket.hpp"


namespace CoreZero
{
	namespace Network
	{
		namespace Sockets
		{

			size_t UdpSocket::SendTo(const uint8_t data[], size_t sendLength, IPv4_Address remoteAddress, uint16_t remotePort)
			{
				return size_t();
			}


			//
			//	Inherited via I_Socket
			//



			int UdpSocket::Connect(const IPv4_Address& remoteEndPoint, uint16_t remotePort)
			{
				SocketOptions sock_opt;
				sock_opt.addr_fam = AddressFamily::IPv4;
				//sock_opt.data_mode = DataMode::DirectPush;
				sock_opt.protocol = ProtocolType::UserDatagram;
				SetOptions(sock_opt);
				return I_Socket::Connect(remoteEndPoint, remotePort);
			}

			int UdpSocket::Listen(const IPv4_Address& localEndPoint, uint16_t localPort)
			{
				SocketOptions sock_opt;
				SetOptions(sock_opt);
				return I_Socket::Listen(localEndPoint, localPort);
			}

			size_t UdpSocket::Send(const uint8_t data[], size_t toSend)
			{
				return I_Socket::Send(data, toSend);
			}

			size_t UdpSocket::SendFile(FILE* fileToSend, fpos_t* filePos)
			{
				return I_Socket::SendFile(fileToSend, filePos);
			}
		}
	}
}