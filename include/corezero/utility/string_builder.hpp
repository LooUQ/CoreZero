/******************************************************************************
*	String builder for string construction. i.e. commands.
*
*	\file	CoreZero.Utility.StringBuilder.h
*	\author	Jensen Miller	<jensen@loouq.com>
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
#ifndef COREZERO_UTILITY_STRINGBUILDER_H_
#define COREZERO_UTILITY_STRINGBUILDER_H_

#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

namespace corezero
{
	namespace utility
	{
		class StringBuilder
		{
		public:
			StringBuilder(decltype(nullptr)) {}
			StringBuilder(const char _init[], size_t _capacity)
				: m_capacity(_capacity)
			{
				m_pCString = new char[_capacity];
				m_length = strlen(_init);
				strcpy(m_pCString, _init);				
			}



			~StringBuilder() { if (m_pCString == nullptr) delete[] m_pCString; }



			inline StringBuilder& operator=(StringBuilder&& otherBuilder)	noexcept
			{
				if (m_pCString) delete[] m_pCString;
				m_pCString = otherBuilder.m_pCString;
				m_capacity = otherBuilder.m_capacity;
				m_length = otherBuilder.m_length;
				otherBuilder.m_pCString = nullptr;
				otherBuilder.m_capacity = 0;
				otherBuilder.m_length = 0;
				return *this;
			}

		public:
			inline StringBuilder& Copy(const char _str[], size_t strLen)
			{				
				m_length = strlen(_str);
				assert(m_length <= m_capacity);
				assert(m_pCString);
				strncpy(m_pCString, _str, m_length);
				return *this;
			}


			inline StringBuilder& Append(const char _ch)
			{
				assert(m_pCString);
				m_pCString[m_length++] = _ch;
				assert(m_length <= m_capacity);
				return *this;
			}



			inline StringBuilder& Append(const char _str[], size_t strLen = 0)
			{
				assert(_str);
				if (strLen == 0) strLen = strlen(_str);				
				assert(m_pCString);
				strncpy(m_pCString + m_length, _str, strLen);
				m_length += strLen;
				assert(m_length <= m_capacity);
				return *this;
			}



			inline StringBuilder& AppendFormat(const char _format[], va_list& _args)
			{
				assert(m_pCString);
				m_length += vsprintf(m_pCString + m_length, _format, _args);
				assert(m_length <= m_capacity);
				return *this;
			}			



			inline int Clear()
			{
				m_length = 0;
				return 0;
			}

			inline const char* AsCString()
			{
				m_pCString[m_length] = '\0';
				return m_pCString;
			}



			void Reset(size_t _pos) { m_length = _pos; }
			size_t Length() const { return m_length; }

		private:
			char* m_pCString = nullptr;
			size_t m_capacity = 0;
			size_t m_length = 0;
		};
	}
}

#endif // !COREZERO_UTILITY_STRINGBUILDER_H_
