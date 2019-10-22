// Copyright (c) 2018 LooUQ Incorporated.

// Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include <corezero/string.hpp>

const size_t corezero::String::NPos = SIZE_MAX;

namespace corezero
{
	/******************************************************************************
 *	@brief Default Constructor
 */
	String::String()
		: m_pCString(nullptr)
		, m_length(0)
	{}



	/******************************************************************************
	*	@brief Copy Constructor
	*/
	String::String(const String& other)
		: m_pCString(nullptr)
		, m_length(other.m_length)
	{
		if (m_length != 0)
		{
			m_pCString = new char[m_length + 1];
			strncpy(m_pCString, other.m_pCString, m_length + 1);
		}
	}



	/******************************************************************************
	*	@brief Move Constructor
	*/
	String::String(String && other) noexcept
		: m_pCString(other.m_pCString)
		, m_length(other.m_length)
	{
		other.m_pCString = nullptr;
		other.m_length = 0;
	}



	/******************************************************************************
	*	@brief Destructor
	*/
	String::~String() noexcept
	{
		if (m_pCString != nullptr) delete m_pCString;
	}



	/******************************************************************************
	*	@brief Copy Assignment Constructor
	*/
	String& String::operator=(const String & other)
	{
		if (other.m_pCString == nullptr) return *this;
		if (m_pCString != nullptr) delete m_pCString;
		
		m_length = other.m_length;
		m_pCString = new char[m_length + 1];
		strncpy(m_pCString, other.m_pCString, m_length + 1);
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
		m_length = other.m_length;
		m_pCString = other.m_pCString;
		//	Delete other string
		other.m_length = 0;
		other.m_pCString = nullptr;
		return *this;
	}

	String& String::operator=(const char* cstring)
	{
		m_length = strlen(cstring);
		m_pCString = new char[m_length + 1];
		strncpy(m_pCString, cstring, m_length + 1);
		return *this;
	}


	/******************************************************************************
	 *	@brief Copy constant character string
	 *
	 *	@param[in] constCString A null-terminated CString
	 */
	String::String(const char* cstring)
		: m_length(strlen(cstring))
	{
		m_pCString = new char[m_length + 1];
		strncpy(m_pCString, cstring, m_length + 1);
	}



	String::String(const char* cstring, size_t length)
		: m_length(length)
	{
		m_pCString = new char[length + 1];
		strncpy(m_pCString, cstring, length);
		m_pCString[length] = NULL;
	}

	int String::reserve(unsigned capacity)
	{
		if (m_pCString == nullptr)
		{
			m_pCString = new char[capacity + 1];
			m_length = 0;
		}
		return capacity;
	}

	int String::refresh()
	{
		m_length = strlen(m_pCString);
		return 0;
	}

	char& String::operator[](size_t index)
	{
		return m_pCString[index];
	}


	const char& String::operator[](size_t index) const
	{
		return m_pCString[index];
	}



	String& String::operator+=(const char* cstring)
	{
		if (cstring == nullptr) return *this;
		size_t added_len = strlen(cstring);
		if (m_pCString != nullptr)
		{
			char* old = m_pCString;
			m_pCString = new char[m_length + added_len + 1];
			strncpy(m_pCString, old, m_length+1);
			delete[] old;
			strcat(m_pCString, cstring);
		}
		else
		{
			m_pCString = new char[added_len + 1];
			strncpy(m_pCString, cstring, added_len + 1);
		}
		m_length += added_len;
		return *this;
	}

	String& String::operator+=(char _char)
	{
		char add_chars[2];
		add_chars[0] = _char;
		add_chars[1] = '\0';
		(*this) += add_chars;
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
		return String(m_pCString+first_pos, length);
	}

	size_t String::Find(const char* cstring, size_t start) const
	{
		if (start > m_length) return -1;		
		return (size_t)(m_pCString - strstr(m_pCString + start, cstring));
	}

	size_t String::Find(const char& ch, size_t start) const
	{
		if (start >= m_length) return NPos;
		return (size_t)(strchr(m_pCString + start, ch)-m_pCString);
	}


	int String::Compare(const String& otherString) const
	{
		if (m_pCString == nullptr || otherString.m_pCString == nullptr) return -1;
		return strcmp(m_pCString, otherString.m_pCString);
	}

	int String::Compare(size_t start, size_t length, const String& otherString) const
	{
		if (m_pCString == nullptr || otherString.m_pCString == nullptr) return -1;
		return strncmp(m_pCString + start, otherString.m_pCString, length);
	}

	int String::Compare(const char* cstring) const
	{
		if (m_pCString == nullptr || cstring == nullptr) return -1;
		return strcmp(m_pCString, cstring);
	}

	int String::Compare(size_t start, size_t length, const char* cstring) const
	{
		if (m_pCString == nullptr || cstring == nullptr) return -1;
		return strncmp(m_pCString + start, cstring, length);
	}

	void String::Clear() noexcept
	{
		m_length = 0;
		if (m_pCString != nullptr) delete[] m_pCString;
		m_pCString = nullptr;
	}
}