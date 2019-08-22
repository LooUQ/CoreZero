/******************************************************************************
*	Author: Jensen Miller
*	Date:	May 9, 2018
*	Company:	LooUQ Inc
*
*	Description:	A lite string class provided for IoT Devices.
*
*	License:
*		The GNU Licence(GNU)
*
*	This file is part of the iotq library.
*
*	IotQc is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	IotQc is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with iotq.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/
#ifndef IOTQC_STRING_H
#define IOTQC_STRING_H

#include <string.h>
#include <stdint.h>


namespace iotq
{
	class String
	{
	public:
		static const size_t NPos;
	//
	//	Constructors
	//
	public:
		// Rule of 5 //
		String();
		String(const String& other);
		String(String&& other) noexcept;
		virtual ~String() noexcept;
		String& operator= (const String& other);
		String& operator= (String&& other) noexcept;	

		template<unsigned N>
		constexpr String(const char(&ctString)[N])
			: m_Length(N - 1)
			, m_pStr(ctString)
		{}

		String& operator= (const char* cstring);
		String(const char* cstring);
		String(const char* cstring, size_t length);

	public:
		const char* c_str() const { return m_pStr; }		
		char* data() { return m_pStr; }
		char& operator[](size_t index);
		const char& operator[](size_t index) const;
		String& operator+=(const char* cstring);
		String& operator+=(const String& otherString);

	public:
		size_t GetLength() const { return m_Length; }
		bool IsEmpty() const { return (m_Length == 0); }
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
		char * m_pStr;
		/// The length of the string w/o null-terminator
		size_t m_Length;
	};
}

#endif // !IOTQC_STRING_H
