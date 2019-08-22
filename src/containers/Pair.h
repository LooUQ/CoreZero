/**
*	Author: Jensen Miller
*	Date:	June 2, 2018
*	Company:	LooUQ Inc
*
*	Description: <DESCRIPTION>
*	License:
*		The GNU Licence(GNU)
*
*		This program is free software: you can redistribute it and/or modify
*		it under the terms of the GNU General Public License as published by
*		the Free Software Foundation, either version 3 of the License, or
*		(at your option) any later version.
*
*		This program is distributed in the hope that it will be useful,
*		but WITHOUT ANY WARRANTY; without even the implied warranty of
*		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*		GNU General Public License for more details.

*		You should have received a copy of the GNU General Public License
*		along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/
#pragma once

#ifndef IOTQC_PAIR_H
#define IOTQC_PAIR_H

#include <stdint.h>

namespace iotq
{
	namespace containers
	{
		template <typename FT, typename ST>
		class CPair
		{
		//
		//	Constructors
		//
		public:
			CPair();
			CPair(FT & firstItem, ST & secondItem);
			CPair(const CPair& other) noexcept;
			CPair(CPair && other) noexcept;
			virtual ~CPair() noexcept;

			CPair& operator= (const CPair& other);
			CPair& operator= (CPair&& other) noexcept;

		//
		//	Methods
		//
		public:
			FT & GetFirst();
			const FT & GetFirst() const;

			ST & GetSecond();
			const ST & GetSecond() const;

			void SetFirst(const FT & first);
			void SetFirst(FT && first);
			
			void SetSecond(const ST & second);
			void SetSecond(ST && sencod);

		//
		//	Associations
		//
		private:
			FT * m_FirstObject = nullptr;
			ST * m_SecondObject = nullptr;
			bool m_FirstAlloc = false;
			bool m_SecondAlloc = false;
		};



		template<typename FT, typename ST>
		CPair<FT, ST>::CPair()
		{}


		template<typename FT, typename ST>
		CPair<FT, ST>::CPair(FT & firstItem, ST & secondItem)
			:
			m_FirstObject(&firstItem),
			m_SecondObject(&secondItem)
		{}


		template<typename FT, typename ST>
		CPair<FT, ST>::CPair(const CPair& other) noexcept
			:
			m_FirstObject(new FT{ *other.m_FirstObject }),
			m_SecondObject(new ST{ *other.m_SecondObject }),
			m_FirstAlloc(true),
			m_SecondAlloc(true)
		{}



		template<typename FT, typename ST>
		CPair<FT, ST>::CPair(CPair && other) noexcept
			:
			m_FirstObject(other.m_FirstObject),
			m_SecondObject(other.m_SecondObject),
			m_FirstAlloc(other.m_FirstAlloc),
			m_SecondAlloc(other.m_SecondAlloc)
		{
			other.m_FirstObject = nullptr;
			other.m_SecondObject = nullptr;
			other.m_FirstAlloc = false;
			other.m_SecondAlloc = false;
		}



		template<typename FT, typename ST>
		CPair<FT, ST>::~CPair() noexcept
		{
			if (m_FirstAlloc)
				delete m_FirstObject;
			if (m_SecondAlloc)
				delete m_SecondObject;
		}

		template<typename FT, typename ST>
		CPair<FT,ST>& CPair<FT, ST>::operator= (const CPair& other)
		{
			if (&other != this)
			{
				if (m_FirstAlloc) delete m_FirstObject;
				if (m_SecondAlloc) delete m_SecondObject;

				m_FirstObject = new FT{ *other.m_FirstObject };
				m_SecondObject = new ST{ *other.m_SecondObject };
				m_FirstAlloc = true;
				m_SecondAlloc = true;
			}

			return *this;
		}


		template<typename FT, typename ST>
		CPair<FT, ST>& CPair<FT, ST>::operator= (CPair&& other) noexcept
		{
			if (&other != this)
			{
				if (m_FirstAlloc) delete m_FirstObject;
				if (m_SecondAlloc) delete m_SecondObject;

				m_FirstObject = other.m_FirstObject;
				m_SecondObject = other.m_SecondObject;
				m_FirstAlloc = other.m_FristAlloc;
				m_SecondAlloc = other.m_SecondAlloc;
			}

			return *this;
		}


		template<typename FT, typename ST>
		FT& CPair<FT, ST>::GetFirst()
		{
			return *m_FirstObject;
		}

		template<typename FT, typename ST>
		const FT& CPair<FT, ST>::GetFirst() const
		{
			return *m_FirstObject;
		}


		template<typename FT, typename ST>
		ST& CPair<FT, ST>::GetSecond()
		{
			return *m_SecondObject;
		}

		template<typename FT, typename ST>
		const ST& CPair<FT, ST>::GetSecond() const
		{
			return *m_SecondObject;
		}


		template<typename FT, typename ST>
		void CPair<FT, ST>::SetFirst(const FT & firstItem)
		{
			if (m_FirstAlloc) delete m_FirstObject;
			m_FirstObject = new FT(firstItem);
			m_FirstAlloc = true;
		}

		template<typename FT, typename ST>
		void CPair<FT, ST>::SetFirst(FT && firstItem)
		{
			m_FirstObject = &firstItem;
			m_FirstAlloc = false;
		}


		template<typename FT, typename ST>
		void CPair<FT, ST>::SetSecond(const ST & secondItem)
		{
			if (m_SecondAlloc) delete m_SecondObject;
			m_SecondObject = new ST(secondItem);
			m_SecondAlloc = true;
		}

		template<typename FT, typename ST>
		void CPair<FT, ST>::SetSecond(ST && secondItem)
		{
			m_SecondObject = &secondItem;
			m_SecondAlloc = false;
		}

		template<typename FT, typename ST>
		CPair<FT, ST>& Make_Pair(const FT& firstItem, const ST& secondItem)
		{
			FT* t_first = new FT(firstItem);
			ST* t_second = new ST(secondItem);
			CPair<FT, ST> t_pair(t_first, t_second, true);
		}
	}
}


#endif // !IOTQC_PAIR_H