/******************************************************************************
*	\file		CoreZero.Threading.Mutex.hpp
*	\author		Jensen Miller
*	\date		July 5, 2018
*
*	Copyright (c) 2018 LooUQ Incorporated
*
*	License: The GNU Licence(GNU)
*
*	This file is part of the CoreZero library.
*
*	CoreZero is free software: you can redistribute it and/or modify it under
*	the terms of the GNU General Public License as published by the
*	Free Software Foundation, either version 3 of the License, or (at
*	your option) any later version.
*
*	CoreZero is distributed in the hope that it will be useful, but WITHOUT
*	ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR
*	PURPOSE.  See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public
*	License along with CoreZero.
*	If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/
#ifndef COREZERO_THREADING_H_
#define COREZERO_THREADING_H_

#include <signal.h>

namespace CoreZero
{
	namespace Threading
	{
		class Mutex
		{
		//
		//	Constructor
		//
		public:
			Mutex() noexcept : m_Key(0) {}
			~Mutex() {}

			
		//
		//	Methods
		//
		public:
			inline void LockSection() { while (m_Key); m_Key = 1; }
			inline void UnlockSection() { m_Key = 0; }
			inline bool TryLockSection() { if (!m_Key) { m_Key = 1; return true; }  return false; }


		//
		//	Attributes
		//
		private:
			sig_atomic_t m_Key;
		};

		class MutexGuard
		{
			Mutex * m_mutex;
		public:
			MutexGuard(Mutex& mut) : m_mutex(&mut) { m_mutex->LockSection(); }
			~MutexGuard() { m_mutex->UnlockSection(); }
		};
	}
}



#endif // !COREZERO_THREADING_H_
