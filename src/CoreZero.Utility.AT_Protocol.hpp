/******************************************************************************
*	AT Protocol class implementation
*
*	\file AT_Protocol.hpp
*	\author Jensen Miller
*
*	Copyright (c) 2019 LooUQ Incorporated.
*
*	License: The GNU License
*
*	This file is part of CoreZero.
*
*   CoreZero is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   CoreZero is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with CoreZero.  If not, see <https://www.gnu.org/licenses/>.
*
******************************************************************************/
#ifndef COREZERO_UTILITY_ATPROTOCOL_H_
#define COREZERO_UTILITY_ATPROTOCOL_H_

#include "atcmd/AT_Def.hpp"
#include "atcmd/AT_Command.hpp"

#include "CoreZero.Async.h"
#include "CoreZero.CompileTime.ConditionalTyping.hpp"

#include "SerialController.hpp"

constexpr const wchar_t PortName[] = L"\\\\.\\COM10";

#define AT_OK	(0)

namespace CoreZero
{
	namespace Utility
	{
		template<>
		class AT_Protocol<false> final
			//: base_thread_coordinator
		{
		public:
			constexpr AT_Protocol()
				: m_bg96(nullptr)
				, m_buffer(nullptr)
				, m_bufSize(0)
				, m_responseLocation(nullptr)
				, m_recentResult(-1)
				, m_awaitingResponse(false)
			{}

			~AT_Protocol();

			void Initialize();

			template <typename ... RESULTS>
			int SendCommand(const AT_Command<RESULTS...>& commandDefinition);

			int SendCommand(const char cmd[]);
			int SendCommandF(const char format[], ...);

			void poll();

		private:
			void send_command();
			void await_result();
			void dispatch_incoming(const char* resultCode);
			void process_out_of_band_data(const char* inData);


		private:
			/// Buffer for command construction.
			char* m_buffer;

			/// Size of command buffer.
			size_t m_bufSize;

			/// Where to put the response.
			char* const* m_responseLocation;

			/// Whether the protocol is awaiting an immediate response.
			bool m_awaitingResponse;

			///	The most recent result code.
			int m_recentResult;

			/// The serial device.
			CSerialDevice* m_bg96;
		};

		template<typename ...RESULTS>
		inline int AT_Protocol<false>::SendCommand(const AT_Command<RESULTS...>& commandDefinition)
		{
			//	set the response location
			m_responseLocation = &commandDefinition.m_buffer;

			//	send the command
			int result = SendCommand(commandDefinition.m_buffer);

			//	reset response location
			m_responseLocation = nullptr;

			return result;
		}




		/*
		template <>
		class AT_Protocol<VERBOSE_RESULTS>	final
		{
		public:
			AT_Protocol();
			~AT_Protocol();

		public:
			template <typename ... RESULTS>
			char* SendCommand(const AT_Command<RESULTS...>& commandDefinition);

			char* SendCommand(const char cmd[]);
			char* SendCommandF(const char format[], ...);
		};
		*/
	}
}

#endif // !COREZERO_UTILITY_ATPROTOCOL_H_