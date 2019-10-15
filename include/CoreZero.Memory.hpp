/******************************************************************************
*	\file	CoreZero.Memory.hpp
*	\author	Jensen Miller
*	\date
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
#ifndef COREZERO_MEMORY_BUFFER_H_
#define COREZERO_MEMORY_BUFFER_H_


namespace CoreZero
{
	namespace Memory
	{
		template <typename T = char>
		class I_Buffer
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

#endif // !COREZERO_BUFFER_H_
