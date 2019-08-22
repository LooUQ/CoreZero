#include "TCPSocket.hpp"

int iotq::network::TcpSocket::Connect(const IPv4_Address & remoteAddress, uint16_t remotePort)
{
	SocketOptions sock_opt;
	sock_opt.addr_fam = IPv4;
	sock_opt.data_mode = DirectPush;
	sock_opt.protocol = TransmissionControl;
	sock_opt.socket_type = Streaming;
	SetOptions(sock_opt);

	return ISocket::Connect(remoteAddress, remotePort);
}

int iotq::network::TcpSocket::Listen(const IPv4_Address & localAddress, uint16_t localPort)
{
	m_Listening = true;
	return TcpSocket::Connect(localAddress, localPort);
}

void iotq::network::TcpSocket::Put(const uint8_t item)
{
	ISocket::Send(&item, 1);
}

size_t iotq::network::TcpSocket::Write(const uint8_t block[], size_t blocksz)
{
	return ISocket::Send(block, blocksz);
}

void iotq::network::TcpSocket::operator<<(const uint8_t block[])
{
	Write(block, strlen((const char*)block));
}

void iotq::network::TcpSocket::operator<<(const iotq::String & data)
{
	(*this) << data.c_str();
}
