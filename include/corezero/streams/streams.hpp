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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../delegate.hpp"
#include "../memory/circular_buffer.hpp"

namespace corezero
{
	template <typename T>
	using WriteMethod = Delegate<unsigned(const T[], unsigned)>;

	template <typename T>
	using ReadMethod = Delegate<unsigned(T[], unsigned)>;

	namespace streams
	{
		//template <typename T = char>
		//struct InputStream
		//{		
		//	InputStream(decltype(nullptr)) {}
		//	InputStream(Memory::I_Buffer<T>* _buffer);
		//	virtual ~InputStream();

		//	virtual size_t Read(T block[], size_t blockSize);
		//	virtual InputStream& ReadLine(T destBuffer[], size_t destSize);

		//	virtual size_t Count() const;

		//	virtual void Seek(size_t _skip);
		//	virtual const T& Peek();
		//	virtual void Flush();

		//private:
		//	Memory::I_Buffer<T>* m_buffer = nullptr;
		//};

		//template <typename T = char>
		//struct OutputStream
		//{		
		//	OutputStream(decltype(nullptr)) {}
		//	OutputStream(Memory::I_Buffer<T>* _buffer);
		//	virtual ~OutputStream();

		//	virtual size_t Write(const T block[], size_t blockSize);
		//	virtual OutputStream& WriteLine(const T srcBuffer[], size_t srcSize);

		//	virtual T Fill() const;
		//	virtual void Fill(T fillItem);

		//	virtual void Seek(size_t _skip);
		//	virtual void Flush();

		//private:
		//	Memory::I_Buffer<T>* m_buffer = nullptr;
		//};

	//	template<typename T = char>
	//	class IO_Stream
	//	{
	//	public:
	//		IO_Stream(decltype(nullptr)) : m_flags(4) {}
	//		IO_Stream(Memory::I_Buffer<T>* inputBuffer, Memory::I_Buffer<T>* outputBuffer);
	//		virtual ~IO_Stream();


	//	//
	//	//	Methods
	//	//
	//	public:
	//		virtual void Put(const T item);
	//		virtual T Get();
	//		virtual size_t Write(const T block[], size_t blockSize);
	//		virtual size_t Read(T block[], size_t blockSize);			
	//		virtual void Seek(size_t _skip);
	//		virtual void Flush();


	//	//
	//	//	Setters & Getters
	//	//
	//	public:
	//		virtual IO_Stream& GetLine(T destBuffer[], size_t destSize);

	//		virtual T Fill() const;
	//		virtual void Fill(T fillItem);

	//		virtual size_t Count() const;

	//	//
	//	//	Attributes
	//	//
	//	private:
	//		/// The current count of items available in the stream.
	//		size_t m_count = 0;

	//		/// The flags representing the current status of the stream.
	//		struct {
	//			uint8_t eofbit : 1;
	//			uint8_t failbit : 1;
	//			uint8_t badbit : 1;
	//			uint8_t goodbit : 1;
	//		} m_flags = { 0 };

	//		/// The input buffer
	//		Memory::I_Buffer<T> * m_inputBuf = nullptr;

	//		/// The output buffer
	//		Memory::I_Buffer<T>* m_outputBuf = nullptr;
	//	};
	//}



	//namespace Streams
	//{
	//	template<typename T>
	//	inline IO_Stream<T>::IO_Stream(Memory::I_Buffer<T>* inputBuffer, Memory::I_Buffer<T>* outputBuffer)
	//		: m_inputBuf(inputBuffer)
	//		, m_outputBuf(outputBuffer)
	//		, m_flags(8)
	//	{
	//		assert	(m_inputBuf);
	//		assert	(m_outputBuf);
	//	}



	//	template<typename T>
	//	inline IO_Stream<T>::~IO_Stream()
	//	{
	//	}



	//	template<typename T>
	//	inline void IO_Stream<T>::Put(const T item)
	//	{
	//		assert	(m_outputBuf);
	//		m_outputBuf->PutT(item);
	//	}



	//	template<typename T>
	//	inline T IO_Stream<T>::Get()
	//	{
	//		assert	(m_inputBuf);
	//		return m_inputBuf->GetT();
	//	}



	//	template<typename T>
	//	inline size_t IO_Stream<T>::Write(const T block[], size_t blockSize)
	//	{
	//		size_t result = m_outputBuf->PutN(block, blockSize);	
	//		m_flags.goodbit = 1;
	//		return result;
	//	}



	//	template<typename T>
	//	inline size_t IO_Stream<T>::Read(T block[], size_t blockSize)
	//	{
	//		if (m_flags.eofbit)
	//			return 0U;

	//		size_t result = m_inputBuf.GetN(block, blockSize);
	//		result == 0U ? m_flags.eofbit = 1 : m_flags.goodbit = 1;
	//		return result;
	//	}



	//	template<typename T>
	//	inline void IO_Stream<T>::Seek(size_t _skip)
	//	{
	//		
	//	}



	//	template<typename T>
	//	inline void IO_Stream<T>::Flush()
	//	{
	//	}



	//	template<typename T>
	//	inline IO_Stream<T>& IO_Stream<T>::GetLine(T destBuffer[], size_t destSize)
	//	{
	//		return *this;
	//	}



	//	template<typename T>
	//	inline T IO_Stream<T>::Fill() const
	//	{
	//		return T();
	//	}



	//	template<typename T>
	//	inline void IO_Stream<T>::Fill(T fillItem)
	//	{
	//	}



	//	template<typename T>
	//	inline size_t IO_Stream<T>::Count() const
	//	{
	//		return size_t();
	//	}
	}
}

#endif

