/******************************************************************************
*	Array class implementation.
*
*	\file	CoreZero.Utility.Array.hpp
*	\author	Jensen Miller	<jensen@loouq.com>
*	\date	May 14, 2018
*
*	Copyright (c) 2018 LooUQ Incorporated.
*
*	License: The GNU License
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
#ifndef COREZERO_UTILTIY_ARRAY_H_
#define COREZERO_UTILTIY_ARRAY_H_

#include <stdint.h>
#include <string.h>

namespace corezero
{
	namespace utility
	{
		/**********************************************************************
		 *	@class Array templated array class.
		 *	@details A templated array that can be filled with N elements of
		 *		type T.
		 */
		template<class T, size_t N=16>
		class Array
		{
		//
		//	Constructors
		//
		public:
			Array();
			Array(const Array& other);
			virtual ~Array();

		//
		//	Methods
		//
		public:
			void Fill(const T& fillValue);
			void Swap(Array&& other);

			T& operator[](size_t index);
			const T& operator[](size_t index) const;
			T& At(size_t index);
			T& Front();
			T& Back();
			T* Data() noexcept;
			const T* Data() const noexcept;

		//
		//	Getters and Setters
		//
		public:
			size_t	GetCapacity() const { return m_Capacity; }

		//
		//	Iterator
		//
		public:
			class iterator
			{
			public:
				iterator(Array* tAry, size_t position) :
					m_TArray(tAry), m_Position(position) {}
				bool operator!=(const iterator &other) const {
					return (m_Position != other.m_Position);
				}
				T& operator*() const {
					return m_TArray->m_Array[m_Position];
				}
				const iterator& operator++() {
					m_Position++;	return *this;
				}

			private:
				Array * m_TArray = nullptr;
				size_t m_Position = 0;
			};

			iterator begin() { return iterator(this, 0); }
			iterator end() { return iterator(this, m_Capacity); }

		//
		//	Attributes
		//
		private:
			/// The capacity
			size_t m_Capacity = N;

			/// The underlying array
			T m_Array[N];
		};




		
		template<class T, size_t N>
		Array<T, N>::Array()
		{
			Fill(T());
		}


		template<class T, size_t N>
		Array<T, N>::Array(const Array& other)
		{			
			size_t to_copy = (m_Capacity < other.m_Capacity) ? m_Capacity : other.m_Capacity;
			memcpy(m_Array, other.m_Array, to_copy * sizeof(T));
		}



		template<class T, size_t N>
		Array<T, N>::~Array()
		{
		}

		template<class T, size_t N>
		void Array<T, N>::Fill(const T& fillValue)
		{
			for (size_t i = 0; i < m_Capacity; i++)
			{
				m_Array[i] = fillValue;
			}
			
		}

		template<class T, size_t N>
		void Array<T, N>::Swap(Array&& other)
		{
			// \NOT_IMPLEMENTED
		}

		template<class T, size_t N>
		T& Array<T, N>::operator[](size_t index)
		{
			return m_Array[index];
		}

		template<class T, size_t N>
		T& Array<T, N>::At(size_t index)
		{
			return m_Array[index];
		}

		template<class T, size_t N>
		T& Array<T, N>::Front()
		{
			return m_Array[0];
		}

		template<class T, size_t N>
		T& Array<T, N>::Back()
		{
			return m_Array[m_Capacity];
		}

		template<class T, size_t N>
		T* Array<T, N>::Data() noexcept
		{
			return m_Array;
		}

		template<class T, size_t N>
		const T* Array<T, N>::Data() const noexcept
		{
			return m_Array;
		}
	}
}

#endif	// !COREZERO_UTILTIY_ARRAY_H_