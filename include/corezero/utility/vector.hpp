/******************************************************************************
*	\file	CoreZero.Utility.Vector.hpp
*	\author	Jensen Miller
*	\date	May 11, 2018
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
#ifndef COREZERO_UTILITY_VECTOR_H_
#define COREZERO_UTILITY_VECTOR_H_

#include "CoreZero.Utility.Array.hpp"

#include <stdint.h>


namespace corezero
{
	namespace utility
	{
		template<class T = int, unsigned int N = 16U>
		class Vector
		{
		public:
			Vector();
			virtual ~Vector();

		public:
			void	Assign(size_t amount, const T& fillValue);
			void	PushBack(const T& item);
			void	PushBack(T&& item);
			void	PopBack();
			void	Insert();
			void	Swap();
			void	Clear();
			void	RemoveCurrent();

			size_t	Resize();
			bool	IsEmpty() const;
			size_t	Reserve(size_t newCapacity);
			size_t	ShrinkToFit();

			T&			operator[](size_t index);
			const T&	operator[](size_t index) const;

			T&	At(size_t index);
			T&	Front();
			T&	Back();
			T&	Data();

			size_t	GetMaxSize() const;
			size_t	GetSize() const;

		//
		//	Iterator
		//
		public:
			class iterator
			{
				friend Vector;
			public:
				iterator(Vector* cVector, size_t position) :
					m_CVector(cVector), m_Position(position) {}
				bool operator!=(const iterator &other) const {
					return (m_Position != other.m_Position);
				}
				T& operator*() const {
					return m_CVector->m_Array[m_Position];
				}
				const iterator& operator++() {
					m_Position++;
					return *this;
				}

				const iterator& operator+(unsigned index) {
					m_Position += index;
					return *this;
				}
			private:
				Vector * m_CVector = nullptr;
				size_t m_Position = 0;
			};

			iterator	begin() { return iterator(this, 0); }
			iterator	end() { return iterator(this, m_Size); }
			void		erase(iterator pos);

		private:
			/// The underlying array of the vector
			TArray<T, N> m_Array;

			/// The current size of the vector
			size_t m_Size = 0;

			/// The capacity of the vector
			size_t m_Capacity = N;

			void SetCurrentIterator(iterator * currentIter) { m_CurrentIter = currentIter; }
			iterator * m_CurrentIter = nullptr;
		};

		template<class T, unsigned int N>
		Vector<T, N>::Vector()
		{
			m_Array.Fill(T());
		}

		template<class T, unsigned int N>
		Vector<T, N>::~Vector()
		{

		}

		template<class T, unsigned int N>
		void Vector<T, N>::Assign(size_t amount, const T& fillValue)
		{
			if (amount > m_Capacity) amount = m_Capacity;
			for (size_t i = 0; i < amount; i++)
			{
				m_Array[i] = fillValue;
			}
		}

		template<class T, unsigned int N>
		void Vector<T, N>::PushBack(const T& item)
		{
			if (m_Size == m_Capacity) return;
			T temp = item;
			m_Array[m_Size++] = temp;			
		}

		template<class T, unsigned int N>
		void Vector<T, N>::PushBack(T&& item)
		{
			if (m_Size == m_Capacity) return;
			m_Array[m_Size++] = item;			
		}

		template<class T, unsigned int N>
		void Vector<T, N>::PopBack()
		{
			if (!m_Size) return;
			m_Array[m_Size] = T();
			m_Size--;
		}

		template<class T, unsigned int N>
		void Vector<T, N>::Insert()
		{

		}

		template<class T, unsigned int N>
		void Vector<T, N>::Swap()
		{

		}

		template<class T, unsigned int N>
		void Vector<T, N>::Clear()
		{
			m_Array.Fill(T());
			m_Size = 0;
		}

		template<class T, unsigned int N>
		void Vector<T, N>::RemoveCurrent()
		{

		}

		template<class T, unsigned int N>
		bool Vector<T, N>::IsEmpty() const
		{
			return !(bool)m_Size;
		}

		template<class T, unsigned int N>
		T& Vector<T, N>::operator[](size_t index)
		{
			return m_Array[index];
		}

		template<class T, unsigned int N>
		const T& Vector<T, N>::operator[](size_t index) const
		{
			return m_Array[index];
		}

		template<class T, unsigned int N>
		T& Vector<T, N>::At(size_t index)
		{
			if (index < m_Size)
			{
				return m_Array[index];
			}
			else return m_Array[0];
		}
		template<class T, unsigned int N>
		inline T & Vector<T, N>::Front()
		{
			return m_Array[0];
		}
		template<class T, unsigned int N>
		T& Vector<T, N>::Back()
		{
			return m_Array[m_Size-1];
		}

		template<class T, unsigned int N>
		size_t Vector<T, N>::GetMaxSize() const
		{
			return m_Capacity;
		}

		template<class T, unsigned int N>
		size_t Vector<T, N>::GetSize()	const
		{
			return m_Size;
		}

		template<class T, unsigned int N>
		inline void Vector<T, N>::erase(iterator pos)
		{
			unsigned erase_pos = pos.m_Position;
			//	Ensure iterator is not an invalid index
			if (erase_pos >= m_Size) return;

			m_Array[erase_pos] = T();
			m_Size--;

			// Is this a pop_back?
			if (erase_pos != m_Size)
			{
				// Shift all subsequent elements down
				for (; erase_pos < m_Size; erase_pos++)
				{
					m_Array[erase_pos] = m_Array[erase_pos + 1];
				}
			}

		}
	}
}

#endif //!COREZERO_UTILITY_H_