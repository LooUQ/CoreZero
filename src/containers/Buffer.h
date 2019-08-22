#pragma once

#ifndef IOTQC_BUFFER_H
#define IOTQC_BUFFER_H
#include "../utilities/Utilities.h"


namespace iotq
{
	namespace containers
	{
		template <typename T = char, unsigned int N = 64U>
		class IBuffer
		{
		public:
			virtual const T&	Peek() const = 0;
			virtual void		Seek(size_t) = 0;
			virtual void PutT(const T& c) = 0;		
			virtual T GetT() = 0;
			virtual unsigned int PutN(const T pArray[], const unsigned int n) = 0;
			virtual unsigned int GetN(T pArray[], const unsigned int n) = 0;
			virtual unsigned int FindT(T findT) const = 0;

			virtual unsigned int GetCapacity() const = 0;
			virtual unsigned int GetLength() const = 0;

		protected:
			virtual unsigned int expandBuffer(unsigned int nMore) = 0;
		};
	}
}

#endif // !IOTQC_BUFFER_H
