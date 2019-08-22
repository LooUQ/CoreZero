/******************************************************************************
*	@file		Mutex.h
*
*	@author		Jensen Miller
*	@date		July 5, 2018
*	@copyright  LooUQ Inc 2018
*
*	@details
*
*	License:
*		The GNU Licence(GNU)
*
*	This file is part of the iotq library.
*
*	IotQc is free software: you can redistribute it and/or modify it under
*	the terms of the GNU General Public License as published by the
*	Free Software Foundation, either version 3 of the License, or (at
*	your option) any later version.
*
*	IotQc is distributed in the hope that it will be useful, but WITHOUT
*	ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR
*	PURPOSE.  See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public
*	License along with iotq.
*	If not, see <http://www.gnu.org/licenses/>.
******************************************************************************/
#pragma once

#ifndef IOTQC_MUTEX_H
#define IOTQC_MUTEX_H

#include <signal.h>
#include "../iotqBase.h"

namespace iotq
{
	namespace threading
	{
		class Mutex
		{
		//
		//	Constructor
		//
		public:
			Mutex() noexcept {}
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

#if defined(MULTI_THREADING)
#define USING_MUTEX
#endif // defined(MULTI_THREADING)


#if defined(USING_MUTEX)
#define LOCK( MUTEX ) MUTEX.LockSection()
#define TRY_LOCK( MUTEX ) MUTEX.TryLockSection()
#define UNLOCK( MUTEX ) MUTEX.UnlockSection()
#else
#define LOCK( MUTEX ) ;
#define TRY_LOCK( MUTEX ) true
#define UNLOCK( MUTEX ) ;
#endif



#endif // !IOTQC_MUTEX_H
