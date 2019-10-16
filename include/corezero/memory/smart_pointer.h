/******************************************************************************
*	\file	CoreZero.Memory.SmartPointer.h
*
*	\author	Jensen Miller
*	\date	Sep 30, 2018
*
*	Copyright (c) LooUQ Incorporated.
*
*	License: The GNU License
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
#ifndef	COREZERO_MEMORY_SMARTPOINTER_H_
#define COREZERO_MEMORY_SMARTPOINTER_H_

namespace corezero
{
	namespace memory
	{
		/**
		 *	@struct ObjectReference SmartPointer "src/framework/SmartPointer.h"
		 *	@brief A reference counting structure. By
		 *		maintaining the reference, this structure can
		 *		issue self-destruction upon zero references.
		 */
		template <typename T>
		struct ObjectReference
		{
			/// The native object pointer
			T * object = nullptr;

			/// The number of references
			unsigned int m_References = 0;

			/// Constructor.
			ObjectReference<T>() {};

			/// Copy constructor			
			/// @param[in] ptrToObj The native handle on the object to maintain.
			ObjectReference<T>(T* ptrToObj) : object(ptrToObj) {}

			/// Destructor. Deletes the object on the heap.
			virtual ~ObjectReference<T>() { delete object; m_References = 0; }

			/// Dereference operator.
			void operator--() {
				m_References--;
				if (m_References <= 0) {
					delete this;
				}
			}

			/// Add reference operator.
			void operator++() {
				m_References++;
			}

			/// Get the number of references.
			/// @returns The number of references.
			unsigned int GetUses() const noexcept { return m_References; }
		};



		/* ----------------------------------------------------------------- */



		/**
		 *	@class SmartPointer SmartPointer.h "src/framework/SmartPointer.h"
		 *	@brief A templated pointer handler.
		 *
		 *	A pointer that utilizes object referencing to
		 *		determine the lifetime of the object it points to.
		 */
		template <typename T>
		class SmartPointer
		{
		public:
			SmartPointer();
			SmartPointer(const SmartPointer& otherPtr);
			SmartPointer(SmartPointer&& otherPtr);

			virtual ~SmartPointer();			
			SmartPointer(T * pointer);

		public:
			virtual void Swap(SmartPointer<T>&& other);
			virtual void Reset();
			virtual T * GetRawPtr();
			bool IsUnique() const noexcept;
			unsigned int GetRefCount() const noexcept;

		public:
			virtual T& operator*() const noexcept;
			virtual T* operator->() const noexcept;
			virtual SmartPointer<T>& operator=(const SmartPointer& smPtr) noexcept;
			virtual T * operator=(T* ownPtr) noexcept;
			virtual T * operator=(const T makePtr) noexcept;
			virtual operator bool() noexcept;

		protected:
			/// Set the reference to a provided object reference.
			/// @param[in] mPtr The object reference pointer.
			void SetReference(ObjectReference<T> * mPtr) { m_Pointer = mPtr; ++(*m_Pointer); }

			/// Gets the reference pointer.
			/// @returns The reference pointer.
			ObjectReference<T> * GetReference() { return m_Pointer; }

			/// Sets ownership of the object referenced.
			/// @param isOwner Whether this SmartPointer is the owner of its object reference.
			void SetOwnership(bool isOwner) noexcept { m_Owner = isOwner; }

			/// Sets the object reference to be expired.
			/// @param[in] isExpired Notify the smartpointer of its object reference expiring.
			void SetExpired(bool isExpired) noexcept { m_Expired = isExpired; }

		protected:
			/// A pointer to the ObjectReference
			ObjectReference<T> * m_Pointer;

			#define Dereference(ptr) --(*ptr)
			#define Reference(ptr) ++(*ptr)

			/// Whether this smartpointer is valid
			bool m_Expired = true;

			/// Whether the object reference is unique to this smart pointer.
			bool m_Owner = false;
		};


		/* ----------------------------------------------------------------------- */

		//
		//	Implmentation
		//

		template <typename T>
		inline SmartPointer<T>::SmartPointer()
			: m_Pointer(nullptr)
		{}

		template <typename T>
		inline SmartPointer<T>::SmartPointer(const SmartPointer& otherPtr)
		{
			m_Expired = otherPtr.m_Expired;
			m_Pointer = otherPtr.m_Pointer;
			if (!m_Expired) Reference(m_Pointer);
		}

		template <typename T>
		inline SmartPointer<T>::SmartPointer(SmartPointer&& otherPtr)
			: SmartPointer((const SmartPointer&)otherPtr)
		{

		}



		/**
		 *	@brief Copy native pointer constructor.
		 *
		 *	Accepts a native pointer to copy and maintain
		 *		its object.
		 *
		 *	@param[in] pointer The pointer to copy for its object.
		 */
		template<typename T>
		inline SmartPointer<T>::SmartPointer(T * pointer)
			: m_Pointer(new ObjectReference<T>(pointer))
			, m_Expired(false)
			, m_Owner(true)
		{
			Reference(m_Pointer);
		}



		/**
		 *	@brief Destructor.
		 *
		 *	Dereference the underlying object reference structure.
		 */
		template<typename T>
		inline SmartPointer<T>::~SmartPointer()
		{
			if (!m_Expired) Dereference(m_Pointer);
		}



		/**
		 *	@brief Swap the object reference with another SmartPointer.
		 *
		 *	By swaping with another smartpointer, the object reference
		 *		is given to the other smartpointer, and this pointer
		 *		receives the providers object reference.
		 *
		 *	@param[in] other The other smart pointer to swap object
		 *		references with.
		 */
		template<typename T>
		inline void SmartPointer<T>::Swap(SmartPointer<T>&& other)
		{
		}



		/**
		 *	@brief Reset the smart pointer.
		 *
		 *	In reseting a smart pointer, the underlying object
		 *		reference is decremented, and this pointer is
		 *		now expired, thus NULL.
		 */
		template<typename T>
		inline void SmartPointer<T>::Reset()
		{
			if (m_Expired) return;
			Dereference(m_Pointer);
			m_Owner = false;
			m_Expired = true;
		}



		/**
		 *	@brief Gets the native pointer.
		 *
		 *	@returns A native pointer to the underlying object.
		 */
		template<typename T>
		inline T * SmartPointer<T>::GetRawPtr()
		{
			if (!m_Expired) return m_Pointer->object;
			else return nullptr;
		}



		/**
		 *	@brief Indicates whether the object reference being maintained
		 *		is unique to this smart pointer.
		 *
		 *	@returns A boolean representing uniqueness of the underlying object.
		 */
		template<typename T>
		inline bool SmartPointer<T>::IsUnique() const noexcept
		{
			if (!m_Expired) return (m_Pointer->GetUses() == 1);
			else return false;
		}



		/**
		 *	@brief Gets the reference count of the object it maintains.
		 *
		 *	@returns The reference count of the maintained object.
		 */
		template<typename T>
		inline unsigned int SmartPointer<T>::GetRefCount() const noexcept
		{
			if (!m_Expired) return m_Pointer->GetUses();
		}



		/**
		 *	@brief Dereferencing operator.
		 *	
		 *	Allows caller to use object as native pointer
		 *		to dereference and access object.
		 *
		 *	@returns A referrence to the object.
		 */
		template<typename T>
		inline T & SmartPointer<T>::operator*() const noexcept
		{
			return *m_Pointer->object;
		}



		/**
		 *	@brief Pointer-to operator.
		 *
		 *	Allows caller to refer to the underlying objects
		 *		members.
		 *
		 *	@returns A pointer to the object for its members.
		 */
		template<typename T>
		inline T * SmartPointer<T>::operator->() const noexcept
		{
			if (!m_Expired) return m_Pointer->object;
			else return nullptr;
		}



		/**
		 *	@brief Copy operator.
		 *
		 *	Copies a smart pointers object reference and increments
		 *		the count of references.
		 *
		 *	@returns A reference to this pointer.
		 */
		template<typename T>
		inline SmartPointer<T> & SmartPointer<T>::operator=(const SmartPointer & smPtr) noexcept
		{
			if (!m_Expired)	Dereference(m_Pointer);
			m_Expired = smPtr.m_Expired;
			m_Pointer = smPtr.m_Pointer;
			if (!m_Expired) Reference(m_Pointer);
			return *this;
		}
		


		/**
		 *	@brief Assignment operator.
		 *
		 *	Assigns the underlying object reference structure to
		 *		maintain the provided native object.
		 *
		 *	@returns A copy of the pointer to the object.
		 */
		template<typename T>
		inline T * SmartPointer<T>::operator=(T * ownPtr) noexcept
		{
			if (!m_Expired) Dereference(m_Pointer);
			m_Pointer = new ObjectReference<T>(ownPtr);
			Reference(m_Pointer);
			m_Expired = false;
			m_Owner = true;
			return ownPtr;
		}



		/**
		 *	@brief Copy native pointer operator.
		 *
		 *	@param[in] makePtr The object to construct, and then point to.
		 *	@returns A pointer to this new object.
		 */
		template<typename T>
		inline T * SmartPointer<T>::operator=(const T makePtr) noexcept
		{
			this->operator=(new T(makePtr));
			return m_Pointer->object;
		}



		/**
		 *	@brief Boolean operator.
		 *	
		 *	Indicates whether this pointer is expired (expired == NULL).
		 */
		template<typename T>
		inline SmartPointer<T>::operator bool() noexcept
		{
			return !m_Expired;
		}
	}
}

#endif	// COREZERO_MEMORY_SMARTPOINTER_H_