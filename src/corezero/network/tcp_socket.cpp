//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include <corezero/network/tcp_socket.hpp>

namespace corezero
{
	namespace network
	{

		//int TcpSocket::Connect(const IPv4_Address& remoteAddress, uint16_t remotePort)
		//{
		//	SocketOptions sock_opt;
		//	sock_opt.addr_fam = IPv4;
		//	//sock_opt.data_mode = DirectPush;
		//	sock_opt.protocol = TransmissionControl;
		//	sock_opt.socket_type = Streaming;
		//	SetOptions(sock_opt);

		//	return I_Socket::Connect(remoteAddress, remotePort);
		//}

		//int TcpSocket::Listen(const IPv4_Address& localAddress, uint16_t localPort)
		//{
		//	m_Listening = true;
		//	return TcpSocket::Connect(localAddress, localPort);
		//}

		//void TcpSocket::Put(const uint8_t item)
		//{
		//	I_Socket::Send(&item, 1);
		//}

		//size_t TcpSocket::Write(const uint8_t block[], size_t blocksz)
		//{
		//	return I_Socket::Send(block, blocksz);
		//}

		//void TcpSocket::operator<<(const uint8_t block[])
		//{
		//	Write(block, strlen((const char*)block));
		//}

		//void TcpSocket::operator<<(const CoreZero::String& data)
		//{
		//	(*this) << data.c_str();
		//}

	}
}