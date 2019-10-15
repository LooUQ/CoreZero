/******************************************************************************
*	AT Command class implementation
*
*	\file AT_Command.hpp
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
#ifndef COREZERO_UTILITY_ATCOMMAND_H_
#define COREZERO_UTILITY_ATCOMMAND_H_

#include "AT_Def.hpp"

#include "CoreZero.String.hpp"
#include "CoreZero.Async.h"

#include <stdio.h>
#include <string.h>

namespace CoreZero
{
	namespace Utility
	{
		template <bool VERBOSE = false>
		class ATProtocol;

		template <typename ... RESULTS>
		class AT_Command final
		{
			friend ATProtocol<false>;
		public:
			template <unsigned N, typename ... CMD_ARGS>
			AT_Command(const char(&command)[N], CMD_ARGS ...  cmdArguments)
				: m_buffer(nullptr)
				, m_bufferSize(0)
				, m_command(command)
				, m_commandLen(N - 1)
				, m_rspParsePtr(nullptr)
			{
				m_buffer = new char[AT_MaxCommandLen];
				strncpy(m_buffer, command, N);
				m_bufferSize += N - 1;

				if (sizeof...(cmdArguments) > 0)
				{
					//	Write Command			
					m_buffer[m_bufferSize++] = AT_WriteOp;
					m_buffer[m_bufferSize] = '\0';
					build_command(cmdArguments...);
				}
			}

			~AT_Command()
			{
				delete[] m_buffer;
			}




		private:
			void concatenate_argument(unsigned arg)
			{
				size_t uint_len = sprintf(m_buffer + m_bufferSize, "%u", arg);
				m_bufferSize += uint_len;
			}


			void concatenate_argument(int arg)
			{				
				size_t int_len = sprintf(m_buffer + m_bufferSize, "%d", arg);				
				m_bufferSize += int_len;
			}


			void concatenate_argument(char arg)
			{
				strncat(m_buffer, &arg, 1);
				m_bufferSize++;
			}


			void concatenate_argument(const char* arg)
			{
				if (arg == nullptr)
				{
					// remove comma
					return;
				}
				size_t c_str_len = strlen(arg);
				sprintf(m_buffer + m_bufferSize, "\"%s\"", arg);				
				m_bufferSize += c_str_len + 2;
			}


		private:
			template <typename ARG_1, typename ... ARGS>
			void build_command(ARG_1 arg, ARGS ... otherArgs)
			{
				concatenate_argument(arg);
				strncat(m_buffer, ",", sizeof(","));
				m_bufferSize++;
				build_command(otherArgs...);
			}


			inline void build_command()
			{
				// Replace comma with carriage return
				m_buffer[--m_bufferSize] = NULL;
			}

		public:
			int Get(bool commandPreceedsResponse, RESULTS& ... results)
			{
				m_rspParsePtr = m_buffer;
				if (commandPreceedsResponse)
				{
					//	Compare command to response
					if (strncmp(m_rspParsePtr, m_command, m_commandLen) != 0)
						return -1;
					else {
						m_rspParsePtr += m_commandLen + 1;	// 1 - ':'
					}
				}

				return get_results(results...);
			}

			template <typename LAMBDATy_>
			void GetAsync(const LAMBDATy_& _callback)
			{
				m_asyncCallback = Create_MemberDelegate(_callback, &LAMBDATy_::operator());
			}

			inline void parse_result(int& intResult)
			{
				sscanf(m_rspParsePtr, "%d", &intResult);
			}

			inline void parse_result(unsigned& uintResult)
			{
				sscanf(m_rspParsePtr, "%u", &uintResult);
			}

			inline void parse_result(char strResult[])
			{
				sscanf(m_rspParsePtr, "%s", strResult);
			}

			inline void parse_result(CoreZero::String& czStringResult)
			{
				sscanf(m_rspParsePtr, "%s", czStringResult.data());
				czStringResult.refresh();
			}


			template <typename RESULT_1, typename ... RESULT_S>
			int get_results(RESULT_1& result_1, RESULT_S& ... results)
			{
				parse_result(result_1);
				if (sizeof...(results) > 0)
				{
					m_rspParsePtr = strchr(m_rspParsePtr, ',');
					if (m_rspParsePtr == NULL) {
						return -1;
					}
					else {
						return get_results(results...);
					}
				}
				return 0;
			}

			int get_results()
			{
				return 0;
			}

#ifdef _DEBUG
		public:
			const char* const Dump() { return m_buffer; }
#endif // _DEBUG


		private:
			CoreZero::Delegate<void(RESULTS...)>* m_asyncCallback = nullptr;

		private:
			const char* m_command;
			const size_t m_commandLen;

			char* m_buffer;
			size_t m_bufferSize;

			const char* m_rspParsePtr;
		};
	}
}

#endif // !COREZERO_UTILITY_ATCOMMAND_H_