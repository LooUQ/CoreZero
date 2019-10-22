//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include <corezero/network/ssl_socket.hpp>

namespace corezero
{
	namespace network
	{
		namespace security
		{
/*			int SSLSocket::Connect(const IPv4_Address& remoteAddress, uint16_t remotePort)
			{
				SocketOptions sock_opt;
				sock_opt.addr_fam = IPv4;
				sock_opt.data_mode = DirectPush;
				sock_opt.protocol = TransmissionControl;
				sock_opt.socket_type = Streaming;
				SetOptions(sock_opt);

				m_Version = TLS1_2;
				m_AuthMode = NO_AUTH;
				m_CipherSuite = ssl_cipher_suite::SUPPORT_ALL;

				uint32_t security_flags = 0;
				security_flags |= (m_Version);
				security_flags |= (m_CipherSuite << 3);
				security_flags |= (m_AuthMode << 19);

				return I_Socket::connect_ssl(security_flags, remoteAddress, remotePort);
			}


			int SSLSocket::Listen(const IPv4_Address& localAddress, uint16_t localPort)
			{
				return -1;
			}

			size_t SSLSocket::Read(uint8_t block[], size_t blocksz)
			{
				return I_Socket::Read(block, blocksz);
			}	*/		
		}
	}
}