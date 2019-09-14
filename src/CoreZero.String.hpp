/******************************************************************************
*	\file	CoreZero.String.hpp
*	\author	Jensen Miller
*	\date	May 9, 2018
*
*	Copyright (c) 2018 LooUQ Incorporated
*
*	License: The GNU Licence(GNU)
*
*	This file is part of the CoreZero library.
*
*	CoreZero is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	CoreZero is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with CoreZero.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/
#ifndef COREZERO_UTILITY_STRING_H_
#define COREZERO_UTILITY_STRING_H_

#include <string.h>
#include <stdint.h>

#ifdef WIN32
#include <iostream>
#endif // WIN32



namespace CoreZero
{
	class String
	{
	public:
		static const size_t NPos;
	//
	//	Constructors
	//
	public:
		template <unsigned N>
		constexpr String(const char(&staticString)[N])
			: m_pCString(staticString)
			, m_length(N-1)
		{}

		// Rule of 5 //
		String();
		String(const String& other);
		String(String&& other) noexcept;
		virtual ~String() noexcept;
		String& operator= (const String& other);
		String& operator= (String&& other) noexcept;
		String& operator= (const char* cstring);
		String(const char* cstring);
		String(const char* cstring, size_t length);

	public:		
		const char* c_str() const { return m_pCString; }		
		char* data() { return m_pCString; }
		int reserve(unsigned capacity);
		int refresh();
		char& operator[](size_t index);
		const char& operator[](size_t index) const;
		String& operator+=(const char* cstring);
		String& operator+=(const String& otherString);

#ifdef WIN32
		friend std::ostream& operator<< (std::ostream& stream, const String& czstring)
		{
			stream << czstring.m_pCString;
			return stream;
		}
#endif // WIN32


	public:
		size_t GetLength() const { return m_length; }		
		bool IsEmpty() const { return (m_length == 0); }
		String SubString(size_t first_pos = 0, size_t length = 0) const;
		size_t Find(const char* cstring, size_t start=0)const;
		size_t Find(const char & ch, size_t start) const;
		int Compare(const String& otherString) const;
		int Compare(size_t start, size_t length, const String& otherString) const;
		int Compare(const char* cstring) const;
		int Compare(size_t start, size_t length, const char* cstring) const;
		void Clear() noexcept;


	private:
		/// The c-string
		char * m_pCString;

		/// The length of the string w/o null-terminator
		size_t m_length;
	};
}

#endif // !COREZERO_UTILITY_STRING_H_
