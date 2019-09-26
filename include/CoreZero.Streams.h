/******************************************************************************
*	\file	CoreZero.Streams.hpp
*	\author	Jensen Miller
*	\date	Aug 16, 2017
*
*	Copyright (c) 2019 LooUQ Incorporated
*
*	\details A stream for I/O software support.
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
#ifndef COREZERO_STREAMS_H_
#define COREZERO_STREAMS_H_

#include <stdint.h>
#include <string.h>

#include "CoreZero.Delegate.hpp"
#include "CoreZero.Memory.RingBuffer.hpp"

namespace CoreZero
{
	template <typename T>
	using WriteMethod = Delegate<unsigned(const T[], unsigned)>;

	template <typename T>
	using ReadMethod = Delegate<unsigned(T[], unsigned)>;

	namespace Streams
	{
		/**********************************************************************
		 *	\class Stream CoreZero.Streams.hpp
		 *	\brief A templated io stream.
		 *	\details An input/output stream class that can N number of T elements.
		 */
		template<typename T = char, unsigned int N = 64U, typename ULBuffer = Memory::RingBuffer<T,N>>
		class Stream
		{
		//
		//	Constructors
		//
		public:
			Stream() : m_Buffer(new ULBuffer) {}
			virtual ~Stream() { delete m_Buffer; }

		protected:
			Stream(ULBuffer * _buffer) : m_Buffer(_buffer) {}


		//
		//	Methods
		//
		public:
			virtual void	Put(const T item);
			virtual T		Get();
			virtual size_t	Write(const T block[], size_t blocksz);
			virtual size_t	Read(T block[], size_t blocksz);
			virtual void	Seek(size_t skipTs);
			virtual bool	AvailableForRead() const;
			virtual bool	AvailableForWrite() const;
			virtual void	Flush();
			virtual size_t	ReadUntil(const T& t);


		//
		//	Operators
		//
		public:
			virtual void operator<<( const T block[] );
			virtual void operator>>( T block[] );
			virtual void operator>>(Stream<T, N, ULBuffer>* otherStream);
			virtual void operator=( const Stream& other );


		//
		//	Getters and Setters
		//
		public:
			size_t GetAvailable() const;
			void SeStreamBlocks(size_t blockSz);
			bool EoF() const;

		protected:
			/// The size of blocks to stream with >><<
			size_t m_SBlockSize = NULL;

			/// The ring buffer holding the data
			Memory::I_Buffer<T,N> * m_Buffer;

		private:
			struct {
				uint8_t	eofbit	:	1;
				uint8_t	failbit :	1;
				uint8_t	badbit	:	1;
				uint8_t	goodbit	:	1;
			} m_Flags;			
		};


		/* ----------------------------------------------------------------------- */



		/**
		 *	@brief Puts T item into stream buffer.
		 *
		 *	@param[in] item The element to put into the stream.
		 */
		template<typename T, unsigned int N, typename ULBuffer>
		inline void Stream<T, N, ULBuffer>::Put(const T item)
		{			
			m_Buffer->PutT(item);
		}

		template<typename T, unsigned int N, typename ULBuffer>
		inline T Stream<T, N, ULBuffer>::Get()
		{
			return m_Buffer->GetT();
		}


		/**
		 *	@brief Writes an array of T elements to the stream.
		 *	
		 *	@param[in] block The block of T elements to copy into the stream.
		 *	@param[in] blocksz The number of T elements in the block.
		 *	@returns The number of T elements that fit into the stream.
		 */
		template<typename T, unsigned int N, typename ULBuffer>
		inline size_t Stream<T, N, ULBuffer>::Write(const T block[], size_t blocksz)
		{
			if (!blocksz) return NULL;
			size_t result;
			result = m_Buffer->PutN(block, blocksz);
			m_Flags.eofbit = 0;						
			return result;
		}



		/**
		 *	@brief Reads elements from the stream.
		 *	
		 *	@param[out] block The block to insert the element into.
		 *	@param[in] blocksz The number of elements to read from the stream.
		 *	@returns The number of elements read into the block.
		 */
		template<typename T, unsigned int N, typename ULBuffer>
		inline size_t Stream<T, N, ULBuffer>::Read(T block[], size_t blocksz)
		{			
			if (m_Flags.eofbit) return NULL;
			
			size_t result = m_Buffer->GetN(block, blocksz);
			if (result == NULL)
			{
				m_Flags.eofbit = 1;
			}
			else
			{
				m_Flags.goodbit = 1;
			}
			return result;
		}



		/**
		 *	@brief Skip through the stream.
		 *
		 *	@param[in] skipTs The number of elements to skip.
		 */
		template<typename T, unsigned int N, typename ULBuffer>
		inline void Stream<T, N, ULBuffer>::Seek(size_t skipTs)
		{
			m_Buffer->Seek(skipTs);
		}



		/**
		 *	@brief Check if data is available for read.
		 *
		 *	@returns Whether the stream has data available for read.
		 */
		template<typename T, unsigned int N, typename ULBuffer>
		inline bool Stream<T, N, ULBuffer>::AvailableForRead() const
		{			
			return (bool)m_Buffer->GetLength();
		}


		/**
		 *	@brief Check if the stream is able to be written to.
		 *
		 *	@returns Whether the stream can be written to.
		 */
		template<typename T, unsigned int N, typename ULBuffer>
		inline bool Stream<T, N, ULBuffer>::AvailableForWrite() const
		{
			return true;
		}



		/** \todo
		 *	@brief Flush the stream
		 */
		template<typename T, unsigned int N, typename ULBuffer>
		inline void Stream<T, N, ULBuffer>::Flush()
		{
			Seek(-1);
		}


		/**
		 *	@brief Read until a specified matching element is found.
		 *
		 *	If a matching element is found, the internal read block
		 *		size is set to the number of elements to read.
		 *
		 *	@param[in] t The element to match and stop.
		 *	@returns The number of elements to read for matching element.
		 */
		template<typename T, unsigned int N, typename ULBuffer>
		inline size_t Stream<T, N, ULBuffer>::ReadUntil(const T& t)
		{
			m_SBlockSize = m_Buffer->FindT(t);
			return m_SBlockSize;
		}



		/**
		 *	@brief Input Operator.
		 *
		 *	Inputs rhs elements into the stream.
		 *
		 *	@param[in] block The rhs elements that will be written to the stream.
		 */
		template<typename T, unsigned int N, typename ULBuffer>
		inline void Stream<T, N, ULBuffer>::operator<<(const T block[])
		{
			if (!m_SBlockSize)
			{
				return;
			}
			else
			{
				Write(block, m_SBlockSize);
			}
		}



		/**
		 *	@brief Output Operator.
		 *
		 *	Outputs elements to a rhs block of elements.
		 *
		 *	@param[out] block The block to insert the elements into.
		 */
		template<typename T, unsigned int N, typename ULBuffer>
		inline void Stream<T, N, ULBuffer>::operator>>(T block[])
		{
			if (!m_SBlockSize)
			{				
				Read(block, m_Buffer->GetLength());
			}
			else
			{
				Read(block, m_SBlockSize);
			}
		}

		template<typename T, unsigned int N, typename ULBuffer>
		inline void Stream<T, N, ULBuffer>::operator>>(Stream<T, N, ULBuffer>* otherStream)
		{
			T * block;
			size_t block_length;
			if (!m_SBlockSize)
			{
				block_length = m_Buffer->GetLength();
			}
			else
			{
				block_length = m_SBlockSize;
			}
			block = new T[block_length];
			Read(block, block_length);
			otherStream->Write(block, block_length);
			delete[] block;
		}



		/**
		 *	@brief Copy assignment operator.
		 *	
		 *	@param[in] other The other stream to copy.
		 */
		template<typename T, unsigned int N, typename ULBuffer>
		inline void Stream<T, N, ULBuffer>::operator=(const Stream & other)
		{			
			this->m_Buffer = other.m_Buffer;
			this->m_SBlockSize = other.m_SBlockSize;
			this->m_Flags = other.m_Flags;
		}



		/**
		 *	@brief Gets the available elements waiting in the stream.
		 *
		 *	@returns The number of elements available.
		 */
		template<typename T, unsigned int N, typename ULBuffer>
		inline size_t Stream<T, N, ULBuffer>::GetAvailable() const
		{			
			return m_Buffer->GetLength();
		}



		/**
		 *	@brief Sets the streaming block size.
		 *
		 *	By setting the streaming block, the stream
		 *		will use this specified size to dictate
		 *		the input and output operators for data
		 *		length.
		 *
		 *	@param[in] blockSz The size of the blocks being inputed/outputed.
		 */
		template<typename T, unsigned int N, typename ULBuffer>
		inline void Stream<T, N, ULBuffer>::SeStreamBlocks(size_t blockSz)
		{
			m_SBlockSize = blockSz;
		}



		/**
		 *	@brief Get the End-of-file flag.
		 *
		 *	@returns Whether the stream is at the end of file.
		 */
		template<typename T, unsigned int N, typename ULBuffer>
		inline bool Stream<T, N, ULBuffer>::EoF() const
		{
			return m_Flags.eofbit;
		}

#pragma endregion

	}
}

#endif

