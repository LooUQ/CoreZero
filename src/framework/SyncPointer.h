/******************************************************************************
*	@file		SyncPointer.h
*
*	@author		Jensen Miller
*	@date		Sep 30, 2018
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

#ifndef IOTQ_SYNCPOINTER_H
#define IOTQ_SYNCPOINTER_H

#include "SmartPointer.h"

namespace iotq
{
	namespace memory
	{
		/**
		 *	@class SyncPointer SyncPointer.h "src/framework/SyncPointer.h"
		 *	@brief A smartpointer that syncs new pointers to a specific location.
		 *	@details When a pointer is created, it defines a location to point to.
		 *		This pointer directs all new derived pointers to this same location
		 *		in order to sync the object they all point to.
		 */
		template <typename T>
		class SyncPointer
			: public SmartPointer<T>
		{
		public:
			SyncPointer();
			SyncPointer(T * pointer);
			virtual ~SyncPointer();

		public:
			virtual void Reset() override;
			virtual T* operator=(T* objPtr) noexcept override;
			virtual SyncPointer<T>& operator=(const SyncPointer<T>& syPtr);
			virtual operator bool() noexcept override;
		};



		/**
		 *	@brief Constructor.
		 *
		 *	Creates an object reference and declares ownership
		 */
		template<typename T>
		inline SyncPointer<T>::SyncPointer()
			: SmartPointer<T>()
		{
			SmartPointer<T>::SetReference(new ObjectReference<T>);
			SmartPointer<T>::SetOwnership(true);
			SmartPointer<T>::SetExpired(false);
		}



		/**
		 *	@brief Construct from pointer.
		 *
		 *	Creates a syncpointer instance with a pointer.
		 */
		template<typename T>
		inline SyncPointer<T>::SyncPointer(T * pointer)
			: SmartPointer<T>(pointer)
		{
		}



		/**
		 *	@brief Destructor.
		 */
		template<typename T>
		inline SyncPointer<T>::~SyncPointer()
		{
		}



		/**
		 *	@brief Reset the pointer to a new object reference.
		 */
		template<typename T>
		inline void SyncPointer<T>::Reset()
		{
			Dereference(SmartPointer<T>::GetReference());
			SmartPointer<T>::SetReference(new ObjectReference<T>);
			SmartPointer<T>::SetOwnership(true);
			SmartPointer<T>::SetExpired(false);
		}


		
		/**
		 *	@brief Assignment operator.
		 *
		 *	Assigns the reference to the provided pointer.
		 */
		template<typename T>
		inline T * SyncPointer<T>::operator=(T * objPtr) noexcept
		{
			if (SmartPointer<T>::GetReference()->object != nullptr)
				delete SmartPointer<T>::GetReference()->object;
			SmartPointer<T>::GetReference()->object = objPtr;
			return SmartPointer<T>::GetReference()->object;
		}



		/**
		 *	@brief Copy operator.
		 *
		 *	Syncs with the provided SyncPointer.
		 */
		template<typename T>
		inline SyncPointer<T>& SyncPointer<T>::operator=(const SyncPointer<T>& syPtr)
		{
			Dereference(SmartPointer<T>::GetReference());
			SmartPointer<T>::SetReference(syPtr.m_Pointer);
			return *this;
		}



		/**
		 *	@brief Boolean operator.
		 *
		 *	Indicates whether this pointer points to
		 *		a valid object.
		 */
		template<typename T>
		inline SyncPointer<T>::operator bool() noexcept
		{
			return (SmartPointer<T>::GetReference()->object != nullptr);
		}
	}
}

#endif // IOTQ_SYNCPOINTER_H