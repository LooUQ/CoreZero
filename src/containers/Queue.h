/******************************************************************************
*	Author: Jensen Miller
*	Date:	May 9, 2018
*	Company:	LooUQ Inc
*
*	Description:	A base templated queue class.
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
#ifndef IOTQC_QUEUE_H
#define IOTQC_QUEUE_H

#include <stdint.h>

#include "Array.h"

namespace iotq
{
	namespace containers
	{
		template<class T, size_t N=8>
		class CQueue
		{
		public:
			CQueue();
			virtual	~CQueue();

		public:
			operator bool() const { return (m_Size > 0); }

		public:
			void	Push(const T& item);
			void	Push(T&& item);
			void	Pop();
			T&		Front() { return m_FifoContainer[m_Front]; }
			T&		Back() { return m_FifoContainer[m_Back]; }
			bool	Empty() { return !m_Size; }
			bool	Full() { return (m_Size == m_Capacity); }
			size_t	GetSize() const { return m_Size; }
			void	Emplace(T& item);
			void	Swap(CQueue& otherQueue);

		private:
			/// The underlying container
			TArray<T, N> m_FifoContainer;

			/// The capacity
			size_t m_Capacity = N;

			/// The object at the front
			size_t m_Front = 0;

			/// The object at the back
			size_t m_Back = 0;

			/// The current size
			size_t m_Size = 0;
		};

		template<class T, size_t N>
		CQueue<T, N>::CQueue()
		{}

		template<class T, size_t N>
		CQueue<T, N>::~CQueue()
		{}

		template<class T, size_t N>
		void CQueue<T, N>::Push(const T& item)
		{
			if (Full())
				return;

			m_FifoContainer[m_Back] = item;
			
			++m_Back %= N;
			++m_Size;
		}

		template<class T, size_t N>
		void CQueue<T, N>::Push(T&& item)
		{
			if (Full())
				return;

			m_FifoContainer[m_Back] = item;

			++m_Back %= N;
			++m_Size;
		}
		
		template<class T, size_t N>
		void CQueue<T, N>::Pop()
		{
			if (Empty())
				return;

			++m_Front %= N;
			--m_Size;
		}

		template<class T, size_t N>
		void CQueue<T, N>::Emplace(T& item)
		{
			// \NOT_IMPLEMENTED
		}

		template<class T, size_t N>
		void CQueue<T, N>::Swap(CQueue& otherQueue)
		{
			// \NOT_IMPLMENTED
		}
	}
}


#endif