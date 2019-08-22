// Copyright (c) 2018 LooUQ Inc. All rights reserved.

// Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include "String.h"

const size_t iotq::String::NPos = SIZE_MAX;

namespace iotq
{
	/******************************************************************************
 *	@brief Default Constructor
 */
	String::String()
		: m_pStr(nullptr)
		, m_Length(0)
	{}



	/******************************************************************************
	*	@brief Copy Constructor
	*/
	String::String(const String& other)
		: m_pStr(nullptr)
		, m_Length(other.m_Length)
	{
		if (m_Length != 0)
		{
			m_pStr = new char[m_Length + 1];
			strncpy(m_pStr, other.m_pStr, m_Length + 1);
		}
	}



	/******************************************************************************
	*	@brief Move Constructor
	*/
	String::String(String && other) noexcept
		: m_pStr(other.m_pStr)
		, m_Length(other.m_Length)
	{
		other.m_pStr = nullptr;
		other.m_Length = 0;
	}



	/******************************************************************************
	*	@brief Destructor
	*/
	String::~String() noexcept
	{
		if (m_pStr != nullptr) delete m_pStr;
	}



	/******************************************************************************
	*	@brief Copy Assignment Constructor
	*/
	String& String::operator=(const String & other)
	{
		if (other.m_pStr == nullptr) return *this;
		if (m_pStr != nullptr) delete m_pStr;
		
		m_Length = other.m_Length;
		m_pStr = new char[m_Length + 1];
		strncpy(m_pStr, other.m_pStr, m_Length + 1);
		return *this;
	}

	/******************************************************************************
	*	@brief Move Assignment Constructor
	*/
	String & String::operator=(String && other) noexcept
	{
		if (this == &other) {
			return *this;
		}
		//	Exact copy
		m_Length = other.m_Length;
		m_pStr = other.m_pStr;
		//	Delete other string
		other.m_Length = 0;
		other.m_pStr = nullptr;
		return *this;
	}

	String& iotq::String::operator=(const char* cstring)
	{
		m_Length = strlen(cstring);
		m_pStr = new char[m_Length + 1];
		strncpy(m_pStr, cstring, m_Length + 1);
		return *this;
	}


	/******************************************************************************
	 *	@brief Copy constant character string
	 *
	 *	@param[in] constCString A null-terminated CString
	 */
	String::String(const char* cstring)
		: m_Length(strlen(cstring))
	{
		m_pStr = new char[m_Length + 1];
		strncpy(m_pStr, cstring, m_Length + 1);
	}



	String::String(const char* cstring, size_t length)
		: m_Length(length)
	{
		m_pStr = new char[length + 1];
		strncpy(m_pStr, cstring, length);
		m_pStr[length] = NULL;
	}

	char& String::operator[](size_t index)
	{
		return m_pStr[index];
	}


	const char& String::operator[](size_t index) const
	{
		return m_pStr[index];
	}



	String& String::operator+=(const char* cstring)
	{
		if (cstring == nullptr) return *this;
		size_t added_len = strlen(cstring);
		if (m_pStr != nullptr)
		{
			char* old = m_pStr;
			m_pStr = new char[m_Length + added_len + 1];
			strncpy(m_pStr, old, m_Length+1);
			delete[] old;
			strcat(m_pStr, cstring);
		}
		else
		{
			m_pStr = new char[added_len + 1];
			strncpy(m_pStr, cstring, added_len + 1);
		}
		m_Length += added_len;
		return *this;
	}

	String & String::operator+=(const String& otherString)
	{
		if (otherString.IsEmpty()) {
			return (*this);
		}
		else
		{
			(*this) += otherString.c_str();
			return (*this);
		}
	}

	String String::SubString(size_t first_pos, size_t length) const
	{
		return String(m_pStr+first_pos, length);
	}

	size_t String::Find(const char* cstring, size_t start) const
	{
		if (start > m_Length) return -1;		
		return (size_t)(m_pStr - strstr(m_pStr + start, cstring));
	}

	size_t String::Find(const char& ch, size_t start) const
	{
		if (start >= m_Length) return NPos;
		return (size_t)(strchr(m_pStr + start, ch)-m_pStr);
	}


	int String::Compare(const String& otherString) const
	{
		if (m_pStr == nullptr || otherString.m_pStr == nullptr) return -1;
		return strcmp(m_pStr, otherString.m_pStr);
	}

	int String::Compare(size_t start, size_t length, const String& otherString) const
	{
		if (m_pStr == nullptr || otherString.m_pStr == nullptr) return -1;
		return strncmp(m_pStr + start, otherString.m_pStr, length);
	}

	int String::Compare(const char* cstring) const
	{
		if (m_pStr == nullptr || cstring == nullptr) return -1;
		return strcmp(m_pStr, cstring);
	}

	int String::Compare(size_t start, size_t length, const char* cstring) const
	{
		if (m_pStr == nullptr || cstring == nullptr) return -1;
		return strncmp(m_pStr + start, cstring, length);
	}

	void String::Clear() noexcept
	{
		m_Length = 0;
		if (m_pStr != nullptr) delete[] m_pStr;
		m_pStr = nullptr;
	}
}