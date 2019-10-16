/******************************************************************************
*	\file	CoreZero.Memory.SmartPointer.h
*
*	\author	Jensen Miller
*	\date	Sep 30, 2018
*
*	Copyright (c) 2018 LooUQ Incorporated.
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
#ifndef COREZERO_MEMORY_COMPOSITEPOINTER_H_
#define COREZERO_MEMORY_COMPOSITEPOINTER_H_

namespace corezero
{
	namespace memory
	{
		template <typename T>
		class CompositePtr;


		/**	A pointer to a owned object, denoting a compositional relationship.
		 *	The owner of a composite ptr owns the object pointed to.
		 */
		template <typename T>
		class CompositePtr
		{
		public:
			constexpr CompositePtr(decltype(nullptr)) noexcept {}
			CompositePtr(T* const dynamicComponent);
			virtual ~CompositePtr();

		public:
			T& operator* () const { return *m_pComponent; }
			T* operator-> () const noexcept { return m_pComponent; }
			T* get() const noexcept { return m_pComponent; }
		private:
			///	A pointer to the object to maintain.
			T* const m_pComponent = nullptr;
		};

		
		template<typename T>
		inline CompositePtr<T>::CompositePtr(T* const dynamicComponent)
			: m_pComponent(dynamicComponent)
		{}

		

		template<typename T>
		inline CompositePtr<T>::~CompositePtr()
		{
			if (m_pComponent == nullptr)
				delete m_pComponent;
		}
	}
}

#endif // !COREZERO_MEMORY_COMPOSITEPOINTER_H_

