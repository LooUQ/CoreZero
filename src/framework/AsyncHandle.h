/******************************************************************************
*	@file		AsyncHandle.h
*
*	@author		Jensen Miller
*	@date		Jun 27, 2018
*	@copyright  LooUQ Inc 2018
*
*	@details	Objects that handle future/awaitable objects.
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

#ifndef IOTQC_ASYNCOBJECT_H
#define IOTQC_ASYNCOBJECT_H


#include <signal.h>
#include "SyncPointer.h"
#include "../multithreading/Thread.h"

#if defined(ARDUINO)
#include <utilities/FunctionObjects.h>
#else
#include "src/utilities/FunctionObjects.h"
#endif

namespace iotq
{
	namespace framework
	{
		/**
		 *	@class IAsync AsyncObject.h "src/framework/AsyncObject.h"
		 *	@brief Defines an interface for async objects.		 
		 */
		class IAsync
		{
		//
		//	Enumerations
		//
		public:
			/// The status of an asychronous operation/object.
			enum async_status
			{
				pending,	///< The object is pending
				available,	///< The object is available
				terminated,	///< The asynchronous operation was terminated
				error		///< There was an error in the asyn operation
			};


		//
		//	Constructors
		//
		public:
			/// Constructor.
			IAsync() : m_Status(pending) {}

			/// Destructor.
			virtual ~IAsync() {}

		public:
			/// Await the requested object.
			void Await() { while (m_Status == pending); }

			/// Abort the awaiting operation.
			void Abort() { m_Status = terminated; }

			/// Get the status of the asynchronous object/operation.
			async_status GetStatus() const { return m_Status; }

		protected:
			/// The current status.
			async_status m_Status;
		};

		using utilities::VoidFunctor;

		/**
		 *	@class AsyncHandle AsyncHandle.h "src/framework/AsyncHandle.h"
		 *	@brief A templated handle class.
		 *
		 *	This class handle object in a "future" fashion. If an asychronous
		 *		operation is required to obtain T object, then use an AsyncHandle
		 *		to refer to that object, obtain statuses and control.
		 */
		template<typename T>
		class AsyncHandle
			: public IAsync
		{

			typedef VoidFunctor <T&> callback_t;

		public:
			/// Default Constructor.
			AsyncHandle() : p_ObjectHandle(new T*), p_Pending(new sig_atomic_t(0)) { *p_ObjectHandle = nullptr; }

			/// Copy Constructor.
			AsyncHandle(const AsyncHandle& other) : p_ObjectHandle(other.p_ObjectHandle), p_Pending(other.p_Pending), m_CanDispose(false) {}

			/// Destructor.
			virtual ~AsyncHandle() { if (m_CanDispose) { delete p_ObjectHandle; delete p_Pending; } }

			/// Copy result.
			void CopyResult(const T& _copy) { **p_ObjectHandle = _copy; *p_Pending = 1; }

			/// Assign result.
			void AssignResult(T* ptrToObject) { *p_ObjectHandle = ptrToObject; *p_Pending = 1; }

			void SaveTo(T * pLocalVar) { *p_ObjectHandle = pLocalVar; }

			void WaitFor()
			{
				while (is_pending())
					threading::this_thread::yield();
			}

			void Renew() { *p_ObjectHandle = nullptr; }



			///	Provide the AsyncHandle with a callback to execute upon object presence.
			///	@param[in] taskRequiringObject A lambda that will be called upon awaited object presense.
			/*
			template <typename LAMBDA>
			void Then(LAMBDA taskRequiringObject) {
				if ((bool)m_PendingObject) { taskRequiringObject(*m_PendingObject); }
				else {
					m_CallbackAction = new VoidFunctor<LAMBDA, VoidFunctor<T&>>(
						new LAMBDA(taskRequiringObject), (void(LAMBDA::*)(T&))&LAMBDA::operator() // Casting away const-ness
						);
				}
			}
			*/

			//template<typename Lambda_T>
			//auto Then(Lambda_T thenDo) // -> decltype(thenDo(*(T*)nullptr))
			//{
			//	AsyncHandle<decltype(thenDo(**p_ObjectHandle))> result;

			//	if (!is_pending())
			//	{
			//		result.Set(thenDo(**p_ObjectHandle));
			//	}
			//	else
			//	{
			//		// Save lambda
			//		;
			//	}

			//	return result;
			//}

		protected:
			/// Calls the callback with the awaited object.
			void call_then() {
				if (m_CallbackAction)
					(*m_CallbackAction)(**p_ObjectHandle);									
			}

			/// Is the asynchronous object pending
			bool is_pending() { return !((bool)*p_Pending); }

		protected:
			/// This handle can dispose of the object handle.
			bool m_CanDispose = true;

			sig_atomic_t * p_Pending;

			/// The object that exists asynchronously.
			T ** volatile p_ObjectHandle;
				
			/// The handling function
			memory::SyncPointer<VoidFunctor<T&>> m_CallbackAction;
		};

		template <typename T>
		class AsyncLocale
		{
			AsyncHandle<T> * h_Handle;
		public:
			AsyncLocale(AsyncHandle<T>& asyncHandle, T& localVar) : h_Handle(&asyncHandle) { asyncHandle.SaveTo(&localVar); }
			virtual ~AsyncLocale() { h_Handle->Renew(); }			
		};
	}
}

#define renew_async(H_ASYNC) H_ASYNC.Renew()

#endif // !IOTQC_ASYNCOBJECT_H
