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

#ifndef IOTQC_RINGBUFFER_H
#define IOTQC_RINGBUFFER_H


#include <stdint.h>
#include <string.h>
#include <math.h>

#include "Array.h"
#include "Buffer.h"




namespace iotq
{
	namespace containers
	{
		/**
		 *	@class Templated ring buffer.
		 *	@details A templated circular buffer that is instantiated to T type
		 *		with a capacity of 64. This buffer can grow, and will wrap reads
		 *		and writes, optimizing out loops on GetT.
		 */
		template<typename T = char, size_t N = 64U, typename container = T * >
		class TRingBuffer
			: public IBuffer<T, N>
		{
			//
			//	Constructors
			//
		public:
			TRingBuffer();
			virtual ~TRingBuffer();


			//
			//	Methods
			//
		public:
			const T & Peek() const;
			virtual void Seek(size_t skips);
			void PutT(const T& c);
			T GetT();
			unsigned int PutN(const T pArray[], const unsigned int n);
			unsigned int GetN(T pArray[], const unsigned int n);
			unsigned int FindT(T findT) const;

		protected:
			unsigned int expandBuffer(unsigned int nMore);



			//
			//	Getters and Setters
			//	
		public:
			unsigned int GetLength() const;
			unsigned int GetCapacity() const;


			//
			//	Iterator
			//
		public:
			class iterator
			{
				//
				//	Constructors
				//
			public:
				iterator(TRingBuffer * cRingBuffer, size_t position) : m_CRingBuffer(cRingBuffer), m_Position(position) {}


				//
				//	Operators
				//
			public:
				bool operator != (const iterator &other) const {
					return ((m_Position != other.m_Position) || !m_CRingBuffer->m_Available);
				}

				T& operator * () const {
					return m_CRingBuffer->m_Buffer[m_Position];
				}

				const iterator& operator ++ () {
					m_Position %= m_CRingBuffer->m_Capacity;
					m_Position++;
					return *this;
				}

				const iterator& operator -- () {
					if (m_Position == 0) m_Position = m_CRingBuffer->m_Capacity;
					else m_Position--;
					return *this;
				}

				size_t operator-(const iterator &other)
				{
					if (m_Position < other.m_Position)
					{
						return m_Position + (m_CRingBuffer->m_Capacity - m_CRingBuffer->m_Begin);
					}
					else
					{
						return m_Position - other.m_Position;
					}
				}

				const T& operator&()
				{
					return m_CRingBuffer->m_Buffer[m_Position];
				}


				//
				//	Attributes
				//
			private:
				size_t m_Position = NULL;


				//
				//	Associations
				//
			private:
				TRingBuffer * m_CRingBuffer = nullptr;
			};

			/// Returns an interator to the current position of the ring buffer
			iterator begin() { return iterator(this, m_Begin); }

			/// Returns an interator to the end of the free buffer segment
			iterator end() { return iterator(this, m_End); }


			//
			//	Attributes
			//
		private:
			/// Capacity of the ring buffer
			size_t m_Capacity;

			/// Currently available data
			volatile size_t m_Length;

			/// The beginning of available data
			size_t m_Begin;

			/// The end of available data
			size_t m_End;

			/// The buffer
			container m_Buffer;
		};


		template<typename T, size_t N, typename container>
		inline TRingBuffer<T, N, container>::TRingBuffer()
			: m_Capacity(N)
			, m_Length(0)
			, m_Begin(0)
			, m_End(0)
			, m_Buffer(new T[N])
		{
		}

		template<typename T, size_t N, typename container>
		inline TRingBuffer<T, N, container>::~TRingBuffer()
		{
			if (m_Buffer == nullptr) { delete m_Buffer; }
		}

		template<typename T, size_t N, typename container>
		inline const T & TRingBuffer<T, N, container>::Peek() const
		{
			return m_Buffer[m_Begin];
		}

		template<typename T, size_t N, typename container>
		inline void TRingBuffer<T, N, container>::Seek(size_t skipTs)
		{
			skipTs = (m_Length < skipTs) ? m_Length : skipTs;
			m_Begin += skipTs;
			m_Length -= skipTs;
			m_Begin %= m_Capacity;
		}

		template<typename T, size_t N, typename container>
		inline void TRingBuffer<T, N, container>::PutT(const T & c)
		{
			if (m_Begin == m_End) { return; }
			m_Buffer[m_End] = c;
			++m_End %= m_Capacity;
			++m_Length;
		}

		template<typename T, size_t N, typename container>
		inline T TRingBuffer<T, N, container>::GetT()
		{
			T& obj = m_Buffer[m_Begin];
			if (m_Length)
			{
				m_Length--;
				++m_Begin %= m_Capacity;
			}
			return obj;
		}

		template<typename T, size_t N, typename container>
		inline unsigned int TRingBuffer<T, N, container>::PutN(const T pArray[], const unsigned int n)
		{
			// If there are no bytes to put, return
			if (!n) { return 0; }

			// Determine whether there is enough room to save the data
			unsigned int spaceAvailable = m_Capacity - m_Length;
			size_t amtToWrite = (spaceAvailable > n) ? n : spaceAvailable;

			if (amtToWrite < n)
			{
				// Prevent buffer overflow //
				expandBuffer(n - amtToWrite);
				amtToWrite = n;
				m_Length += amtToWrite;
			}
			else
			{
				// No buffer overflow //
				m_Length += amtToWrite;
				size_t spaceToFull = m_Capacity - m_End;
				if (amtToWrite > spaceToFull)
				{
					// Wrap the write //
					memcpy(&m_Buffer[m_End], pArray, spaceToFull * sizeof(T));
					amtToWrite -= spaceToFull;
					pArray += spaceToFull;
					m_End = 0;
				}
			}

			// Copy the (remaining) data
			memcpy(&m_Buffer[m_End], pArray, amtToWrite * sizeof(T));
			m_End += amtToWrite; m_End %= m_Capacity;
			return n;
		}

		template<typename T, size_t N, typename container>
		inline unsigned int TRingBuffer<T, N, container>::GetN(T pArray[], const unsigned int n)
		{
			if ((!n) || (!m_Length)) { return NULL; }

			size_t amt_to_read = (m_Length > n) ? n : m_Length;
			m_Length -= amt_to_read;

			size_t space_to_cap = m_Capacity - m_Begin ;
			if (amt_to_read > space_to_cap)
			{
				// Wrap the read
				if (space_to_cap)
				{
					memcpy(pArray, &m_Buffer[m_Begin], space_to_cap * sizeof(T));
					amt_to_read -= space_to_cap;
					pArray += space_to_cap;
				}
 				m_Begin = NULL;
			}
			else
			{
				space_to_cap = 0;
			}

			// Copy the (remaining) data
			memcpy(pArray, &m_Buffer[m_Begin], amt_to_read * sizeof(T));
			m_Begin += amt_to_read; m_Begin %= m_Capacity;
			return amt_to_read + space_to_cap;
		}

		template<typename T, size_t N, typename container>
		inline unsigned int TRingBuffer<T, N, container>::FindT(T findT) const
		{
			if (m_Length == 0) { return 0; }

			size_t begin = m_Begin;
			size_t length = 0;

			if (GetLength())
				do
				{
					T& t = m_Buffer[begin];
					++begin %= m_Capacity;
					length++;
					if (t == findT) {
						return length;
					}
				} while(begin != m_End);
			return 0;
		}

		template<typename T, size_t N, typename container>
		inline unsigned int TRingBuffer<T, N, container>::expandBuffer(unsigned int nMore)
		{
			// Save state of available data
			size_t temp_available = m_Length;

			// Create new buffer and copy
			T * new_buffer = new T[m_Capacity + nMore];
			GetN(new_buffer, m_Length);

			// Restore new state
			m_Begin = NULL;
			m_Length = m_End = temp_available;
			m_Capacity += nMore;

			// Dispose of old buffer and point to new
			delete[] m_Buffer;
			m_Buffer = new_buffer;
			return m_Capacity;
		}



		template<typename T, size_t N, typename container>
		inline unsigned int TRingBuffer<T, N, container>::GetLength() const
		{
			return m_Length;
		}

		template<typename T, size_t N, typename container>
		inline unsigned int TRingBuffer<T, N, container>::GetCapacity() const
		{
			return m_Capacity;
		}
	}
}

typedef iotq::containers::TRingBuffer<> StringRing;

#endif // !IOTQC_RINGBUFFER_H