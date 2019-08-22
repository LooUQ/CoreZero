
#include "NetworkAdapter.hpp"

#include "Socket.hpp"
#include "sockets/UDPSocket.hpp"
#include "sockets/TCPSocket.hpp"

static iotq::network::INetworkAdapter* g_DefaultNetworkAdapter = nullptr;

namespace iotq
{
	namespace network
	{
		void INetworkAdapter::SetAsDefault()
		{
			g_DefaultNetworkAdapter = this;
		}

		INetworkAdapter * INetworkAdapter::GetDefault()
		{
			return g_DefaultNetworkAdapter;
		}
	}
}
