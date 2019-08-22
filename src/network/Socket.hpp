/******************************************************************************
*	@file		LLSockets.h
*
*	@author		Jensen Miller
*	@date		Dec 18, 2018
*	@copyright	LooUQ Inc 2018
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

/**
 *	Do not use the iotq OO implementation of sockets if the unix
 *		implementation of sockets <sys/socket.h> is included.
 */
#ifndef _SYS_SOCKET_H

#ifndef IOTQ_SOCKETS_H
#define IOTQ_SOCKETS_H

#include <stdint.h>

#include "NetworkAdapter.hpp"
#include "../containers/RingBuffer.h"

namespace iotq
{
	namespace network
	{
		typedef enum
		{
			Raw,
			Streaming,
			Datagram,
			Sequenced
		} SocketType;



		typedef struct
		{
			ProtocolType protocol;
			DataMode data_mode;
			AddressFamily addr_fam;
			SocketType socket_type;			
		} SocketOptions;

		constexpr uint32_t ProtocolType_MSK = 0xF00;

		static inline uint32_t SocketOptions_to_flags(const SocketOptions& sockOpts)
		{
			uint32_t flags = 0;
			flags |= sockOpts.addr_fam;
			flags |= sockOpts.data_mode << 4;
			flags |= sockOpts.protocol << 8;
			flags |= sockOpts.socket_type << 12;
			return flags;
		}



		/**
		 *	@class ISocket
		 *
		 *	Sockets are representative of connections opened on a
		 *		network adapter. They can be utilized similarly to I/O
		 *		operations on a file.
		 */
		class ISocket
		{
		//
		//	Constructors
		//
		public:
			ISocket() : m_NetworkAdapter(INetworkAdapter::GetDefault()) {}
			virtual ~ISocket() {}


		//
		//	Methods
		//
		public:		
			virtual int Close() {
				return m_NetworkAdapter->Disconnect(m_ID, 10);
			}

			virtual int Connect(const char remoteAddress[], uint16_t remotePort) {
				return Connect(remoteAddress, remotePort);
			}

			virtual int	Connect(const IPv4_Address& remoteAddress, uint16_t remotePort) {
				if (m_NetworkAdapter == nullptr) m_NetworkAdapter = INetworkAdapter::GetDefault();
				return m_NetworkAdapter->Connect(m_ID, SocketOptions_to_flags(m_Options), remoteAddress, remotePort);
			}			

			virtual int	Listen(const IPv4_Address& localEndPoint, uint16_t localPort) {
				return m_NetworkAdapter->Listen(m_ID, SocketOptions_to_flags(m_Options), localEndPoint, localPort);
			}

			virtual size_t	Send(const uint8_t data[], size_t toSend) {
				return m_NetworkAdapter->Send(m_ID, data, toSend);
			}

			virtual size_t	SendFile(FILE* fileToSend, fpos_t* filePos = NULL) {
				return m_NetworkAdapter->SendFile(m_ID, fileToSend, filePos);
			}

			virtual size_t Read(uint8_t data[], size_t dataLength)
			{
				return m_NetworkAdapter->Receive(m_ID, data, dataLength);
			}

		protected:
			virtual int connect_ssl(uint32_t securityFlags, const IPv4_Address& remoteAddress, uint16_t remotePort) {
				if (m_NetworkAdapter == nullptr) m_NetworkAdapter = INetworkAdapter::GetDefault();
				return m_NetworkAdapter->ConnectSSL(m_ID, SocketOptions_to_flags(m_Options), securityFlags, remoteAddress, remotePort);
			}

		public:
			bool IsOpen() const { return m_Open; }
			bool IsListening() const { return m_Listening; }
			int GetId() const { return m_ID; }
			const SocketOptions GetOptions() const { return m_Options; }
			void SetOptions(const SocketOptions& sockOpts) { m_Options = sockOpts; }			

		//
		//	Attributes
		//
		protected:
			/// The Id of this ISocket.
			int m_ID = 0;

			/// Whether the socket is open.
			bool m_Open = false;

			/// Whether the socket is listening.
			bool m_Listening = false;

			/// Socket Options
			SocketOptions m_Options;


		//
		//	Associations
		//
		protected:
			/// The network adapter that opened this socket.
			INetworkAdapter * m_NetworkAdapter;
		};



		class SocketManager
		{
		public:
			SocketManager() : SocketManager(32) {}
			SocketManager(unsigned int idRange) : m_MaxSocketId(idRange), m_SocketMap(new ISocket*[idRange])
			{ for (; idRange > 0; idRange--) m_SocketMap[idRange - 1] = nullptr; }

			~SocketManager() {}

		public:
			void ManageSocket(ISocket * socket)
			{ m_SocketMap[socket->GetId()] = socket; }

			void UnmanageSocket(ISocket * socket)
			{ UnmanageSocket(socket->GetId()); }

			void UnmanageSocket(unsigned int socket)
			{ m_SocketMap[socket] = nullptr; }
			
			ISocket * operator[] (unsigned int socket)
			{ return m_SocketMap[socket]; }

		private:
			unsigned int m_MaxSocketId;
			ISocket ** m_SocketMap;
		};
	}
}


#endif // !IOTQ_SOCKETS_H

#endif // !_SYS_SOCKET_H