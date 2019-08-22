/******************************************************************************
*	Author: Jensen Miller
*	Date:	Jul 23, 2018
*	Company:	LooUQ Inc
*
*	Description:	Thread class for multiprocessing. If the system is single threaded,
*						the system implements protothreading.
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

#ifndef IOTQC_THREAD_H
#define IOTQC_THREAD_H

#include "../utilities/FunctionObjects.h"

namespace iotq
{
	namespace threading
	{
		class Thread
		{
		private:
			Thread(utilities::VoidFunctor<> * voidReturningFunction);

		public:
			Thread() noexcept {}

			Thread(void(*voidFunction)(void));			

			template<typename T>
			Thread(void(T::*classMemberFn)(void), T * classInstance)
				: Thread(new utilities::VoidFunctor<T, utilities::VoidFunctor<>>(classInstance, classMemberFn)) {}

			~Thread();

		public:
			///	@brief Get the ID of the thread.
			///	@returns The ID.
			unsigned int GetId() const { return m_tid; }

			/// @brief Awaits this thread to join the calling thread.
			void Join();

			/// @brief Queries if the thread is joinable.
			bool IsJoinable() const noexcept { return !m_IsDetached; }

			///	@brief Detaches this thread from the constructing thread.
			void Detach();

		private:
			unsigned int m_tid;
			bool m_IsDetached = false;
		};

		struct this_thread
		{
			static void yield() noexcept;
			static void sleep_for(unsigned long milli_s);
		};
	}
}

#endif // !IOTQC_THREAD_H

