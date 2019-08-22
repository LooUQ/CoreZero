/******************************************************************************
*	Author: Jensen Miller
*	Date:	May 14, 2018
*	Company:	LooUQ Inc
*
*	Description:	A base templated array class.
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

#ifndef IOTQC_ARRAY_H
#define IOTQC_ARRAY_H

#include <stdint.h>
#include <string.h>

namespace iotq
{
	namespace containers
	{
		/**
		 *	@class TArray templated array class.
		 *	@details A templated array that can be filled with N elements of
		 *		type T.
		 */
		template<class T, size_t N=16>
		class TArray
		{
		//
		//	Constructors
		//
		public:
			TArray();
			TArray(const TArray& other);
			virtual ~TArray();

		//
		//	Methods
		//
		public:
			void Fill(const T& fillValue);
			void Swap(TArray&& other);

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
				iterator(TArray* tAry, size_t position) :
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
				TArray * m_TArray = nullptr;
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
		TArray<T, N>::TArray()
		{
			Fill(T());
		}


		template<class T, size_t N>
		TArray<T, N>::TArray(const TArray& other)
		{			
			size_t to_copy = (m_Capacity < other.m_Capacity) ? m_Capacity : other.m_Capacity;
			memcpy(m_Array, other.m_Array, to_copy * sizeof(T));
		}



		template<class T, size_t N>
		TArray<T, N>::~TArray()
		{
		}

		template<class T, size_t N>
		void TArray<T, N>::Fill(const T& fillValue)
		{
			for (size_t i = 0; i < m_Capacity; i++)
			{
				m_Array[i] = fillValue;
			}
			
		}

		template<class T, size_t N>
		void TArray<T, N>::Swap(TArray&& other)
		{
			// \NOT_IMPLEMENTED
		}

		template<class T, size_t N>
		T& TArray<T, N>::operator[](size_t index)
		{
			return m_Array[index];
		}

		template<class T, size_t N>
		T& TArray<T, N>::At(size_t index)
		{
			return m_Array[index];
		}

		template<class T, size_t N>
		T& TArray<T, N>::Front()
		{
			return m_Array[0];
		}

		template<class T, size_t N>
		T& TArray<T, N>::Back()
		{
			return m_Array[m_Capacity];
		}

		template<class T, size_t N>
		T* TArray<T, N>::Data() noexcept
		{
			return m_Array;
		}

		template<class T, size_t N>
		const T* TArray<T, N>::Data() const noexcept
		{
			return m_Array;
		}
	}
}

#endif