/******************************************************************************
*	\file	CoreZero.Utility.AT_Protocol.h
*	\author	Jensen Miller
*	\details AT Protocol class implementation
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

#include "../src/atcmd/AT_Def.hpp"
#include "../src/atcmd/AT_Command.hpp"
#include <CZSystem.Communication.h>
#include "CoreZero.Memory.hpp"
#include "CoreZero.Utility.StringBuilder.h"
#include "CoreZero.Async.h"
#include "CoreZero.CompileTime.ConditionalTyping.hpp"

#define AT_OK	(0)

namespace CoreZero
{
	namespace Utility
	{
		/**********************************************************************
		 *	AT_Protocol operating with numeric results.
		 */
		template<>
		class AT_Protocol<false> final
		{
		public:
			enum response_val
			{
				ok =			0x00,
				error =			0x04,
				ready_data =	0x11,
				no_CR =			0xFF
			};
		//
		//	Constructors.
		//
		public:		
			AT_Protocol(decltype(nullptr)) {}
			AT_Protocol(Delegate<size_t(const char*, size_t)>* writeCommandMethod);
			
			AT_Protocol& operator=(AT_Protocol&& otherProtocol) noexcept;

			~AT_Protocol();


		//
		//	Methods
		//
		public:
			template <typename ... RESULTS>
			int SendCommand(const AT_Command<RESULTS...>& commandDefinition);
			int SendCommand(const char cmd[]);
			int SendCommandF(const char format[], ...);			

			int Parse(const char* responseData, size_t responseLen);

		private:
			void send_command();
			void await_result();
			void dispatch_incoming(const char* resultCode);
			void process_out_of_band_data(const char* inData);


		//
		//	Attributes
		//
		private:
			Delegate<size_t(const char*, size_t)>* m_writeFn = nullptr;

			/// Pointer to buffer receiving responses.
			Memory::I_Buffer<char>* const m_pComBuffer = nullptr;

			/// Buffer for command construction.
			StringBuilder m_commandBuilder = nullptr;

			/// Where to put the response.
			char* const* m_responseLocation = nullptr;

			/// Whether the protocol is awaiting an immediate response.
			volatile bool m_awaitingResponse = false;

			///	The most recent result code.
			int m_recentResult = 0;
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