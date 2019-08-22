#include "UDPSocket.hpp"


namespace iotq
{
	namespace network
	{
		size_t UdpSocket::SendTo(const uint8_t data[], size_t sendLength, IPv4_Address remoteAddress, uint16_t remotePort)
		{
			return size_t();
		}


		//
		//	Inherited via ISocket
		//



		int UdpSocket::Connect(const IPv4_Address& remoteEndPoint, uint16_t remotePort)
		{
			SocketOptions sock_opt;
			sock_opt.addr_fam = AddressFamily::IPv4;
			sock_opt.data_mode = DataMode::DirectPush;
			sock_opt.protocol = ProtocolType::UserDatagram;
			SetOptions(sock_opt);
			return ISocket::Connect(remoteEndPoint, remotePort);
		}

		int UdpSocket::Listen(const IPv4_Address& localEndPoint, uint16_t localPort)
		{
			SocketOptions sock_opt;
			SetOptions(sock_opt);
			return ISocket::Listen(localEndPoint, localPort);
		}

		size_t UdpSocket::Send(const uint8_t data[], size_t toSend)
		{
			return ISocket::Send(data, toSend);
		}

		size_t UdpSocket::SendFile(FILE* fileToSend, fpos_t* filePos)
		{
			return ISocket::SendFile(fileToSend, filePos);
		}
	}
}