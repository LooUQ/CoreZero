#pragma once

#ifndef IOTQ_CORE_H
#define IOTQ_CORE_H

//
//	Compile-Time objects
//
#include "tct_objects/CTString.h"

//
//	Framework objects
//
#include "framework/AsyncHandle.h"
#include "framework/SmartPointer.h"

//
//	Utilities
//
#include "utilities/Utilities.h"
#include "utilities/String.h"
#include "utilities/macros.h"
#include "utilities/FunctionObjects.h"

//
//	Input / Output
//
#include "io/Stream.h"
#include "io/ATCommandProtocol.hpp"

//
//	Containers
//
#include "containers/Array.h"
#include "containers/Vector.h"
#include "containers/Queue.h"
#include "containers/Pair.h"
#include "containers/RingBuffer.h"

//
//	Network
//
#include "network/Addressing.hpp"
#include "network/NetworkAdapter.hpp"
#include "network/ICellularAdapter.hpp"
#include "network/IModem.hpp"
#include "network/Radio.hpp"
#include "network/Socket.hpp"
//	Sockets
#include "network/sockets/UDPSocket.hpp"
#include "network/sockets/TCPSocket.hpp"
#include "network/sockets/SSLSocket.hpp"

#endif // !IOTQ_CORE_H