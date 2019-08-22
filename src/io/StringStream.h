/******************************************************************************
*	Author: Jensen Miller
*	Date:	Aug 16, 2017
*	Company:	LooUQ Inc
*
*	Description:	A bytestream for simple I/O support in software.
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
#pragma once

#ifndef IOTQC_SSTREAM_H
#define IOTQC_SSTREAM_H

#include "Stream.h"
#include "../framework/Event.h"


namespace iotq
{
	namespace streams
	{
		template<size_t N = 64>
		class SStream : TStream<char, N>
		{
		public:
			enum Break_T
			{
				NoBreaking,
				Tokenizing,
				Comparing
			};
		public:
			SStream() {}
			virtual ~SStream() {}

		public:
			virtual void	ReadUntil(char * t) override;
			virtual void	Find(const char * substr);
			virtual void	TokenizeBy(const char* delims);
			virtual void	CompareWith(const char strCmp);
			virtual void	Detokenize(const char repl);


			virtual void	operator>>(char str[]) override;
			virtual void	operator<<(const char str[]) override;
			const char * PeekToken();

			size_t	GetNextTokSize();

		private:
			const char * m_Cntrls = nullptr;
			char m_Cmp = NULL;
			Break_T m_Method = NoBreaking;
		};
	}
}


template<size_t N>
void iotq::streams::SStream<N>::ReadUntil(char * t)
{

}

template<size_t N>
void iotq::streams::SStream<N>::Find(const char * substr)
{
}

template<size_t N>
void iotq::streams::SStream<N>::TokenizeBy(const char * delims)
{
	m_Cntrls = delims;
}

template<size_t N>
void iotq::streams::SStream<N>::CompareWith(const char strBrks)
{
	m_Cmp = strBrks;
}

template<size_t N>
void iotq::streams::SStream<N>::Detokenize(const char repl)
{

}

template<size_t N>
void iotq::streams::SStream<N>::operator>>(char str[])
{
	//size_t str_len = NULL;
	//switch (m_Method)
	//{
	//case NoBreaking:
	//	TStream<char, N>::operator>>(str);
	//	break;
	//case Tokenizing:
	//	strtok(this->m_Buffer->GetBuffer(), m_Cntrls);
	//	for (char c : *this->m_Buffer)
	//	{
	//		str_len++;
	//		if (c == '\0')
	//		{
	//			Read(str, str_len);
	//			this->m_Buffer->GetT();
	//			break;
	//		}
	//	}
	//	break;
	//case Comparing:
	//	for (char c : *m_Buffer)
	//	{
	//		str_len++;
	//		if (c < m_Cmp)
	//		{
	//			Read(str, str_len);
	//			m_Buffer->GetT();
	//			break;
	//		}
	//	}
	//	break;
	//default:
	//	TStream<char, N>::operator>>(str);
	//	break;
	//}
}

template<size_t N>
void iotq::streams::SStream<N>::operator<<(const char str[])
{
	//size_t str_len = strlen(str);
	//Write(str, str_len);
}

template<size_t N>
const char * iotq::streams::SStream<N>::PeekToken()
{
	return nullptr;
}

template<size_t N>
size_t iotq::streams::SStream<N>::GetNextTokSize()
{
	return size_t();
}


#endif // !IOTQC_SSTREAM_H