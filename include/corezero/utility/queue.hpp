/******************************************************************************
*	\file	CoreZero.Utility.Queue.hpp
*	\author	Jensen Miller
*	\date	May 9, 2018
*
*	Copyright (c) 2019 LooUQ Incorporated
*
*	\details
*
*	License: The GNU Licence(GNU)
*
*	This file is part of the CoreZero library.
*
*	CoreZero is free software: you can redistribute it and/or modify it
*	under the terms of the GNU General Public License as published by the
*	Free Software Foundation, either version 3 of the License, or (at your
*	option) any later version.
*
*	CoreZero is distributed in the hope that it will be useful, but
*	WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
*	Public License for more details.
*
*	You should have received a copy of the GNU General Public License along
*	with CoreZero.
*	If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/
#ifndef COREZERO_UTILITY_QUEUE_H_
#define COREZERO_UTILITY_QUEUE_H_

#include <stdint.h>

#include "array.hpp"

namespace corezero
{
	namespace utility
	{
		template<class T, size_t N=8>
		class Queue
		{
		public:
			Queue();
			virtual	~Queue();

		public:
			operator bool() const { return (m_Size > 0); }

		public:
			void	Enqueue(const T& item);
			void	Enqueue(T&& item);
			void	Dequeue();
			T&		Front() { return m_FifoContainer[m_Front]; }
			T&		Back() { return m_FifoContainer[m_Back]; }
			bool	Empty() { return !m_Size; }
			bool	Full() { return (m_Size == m_Capacity); }
			size_t	GetSize() const { return m_Size; }
			void	Emplace(T& item);
			void	Swap(Queue& otherQueue);

		private:
			/// The underlying container
			Array<T, N> m_FifoContainer;

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
		Queue<T, N>::Queue()
		{}

		template<class T, size_t N>
		Queue<T, N>::~Queue()
		{}

		template<class T, size_t N>
		void Queue<T, N>::Enqueue(const T& item)
		{
			if (Full())
				return;

			m_FifoContainer[m_Back] = item;
			
			++m_Back %= N;
			++m_Size;
		}

		template<class T, size_t N>
		void Queue<T, N>::Enqueue(T&& item)
		{
			if (Full())
				return;

			m_FifoContainer[m_Back] = item;

			++m_Back %= N;
			++m_Size;
		}
		
		template<class T, size_t N>
		void Queue<T, N>::Dequeue()
		{
			if (Empty())
				return;

			++m_Front %= N;
			--m_Size;
		}

		template<class T, size_t N>
		void Queue<T, N>::Emplace(T& item)
		{
			// \NOT_IMPLEMENTED
		}

		template<class T, size_t N>
		void Queue<T, N>::Swap(Queue& otherQueue)
		{
			// \NOT_IMPLMENTED
		}
	}
}


#endif	// !COREZERO_UTILITY_QUEUE_H_