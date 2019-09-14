/******************************************************************************
*	Compile time conditional branching for types.
*
*	\file conditional_typing.h
*	\author Jensen Miller
*
*	Copyright (c) 2019 LooUQ Incorporated.
*
*	License: The GNU License
*
*	This file is part of CoreZero.
*
*   CoreZero is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   CoreZero is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with CoreZero.  If not, see <https://www.gnu.org/licenses/>.
*
******************************************************************************/
#ifndef COREZERO_CTCONDITIONAL_H
#define COREZERO_CTCONDITIONAL_H

namespace CoreZero
{
	namespace CompileTime
	{
		/**
		 *	\brief Syntax of conditional typing. Use 'EvaluatedType'.
		 */
		template<bool Expression, typename TypeIfTrue, typename TypeIfFalse>
		struct CT_IF;

		/**
		 *	\brief Type if expression is true. Use 'EvaluatedType'.
		 */
		template <typename TypeIfTrue, typename TypeIfFalse>
		struct CT_IF<true, TypeIfTrue, TypeIfFalse>
		{
			using EvaluatedType = TypeIfTrue;
		};

		/**
		 *	\brief Type if expression is false. Use 'EvaluatedType'.
		 */
		template <typename TypeIfTrue, typename TypeIfFalse>
		struct CT_IF<false, TypeIfTrue, TypeIfFalse>
		{
			using EvaluatedType = TypeIfFalse;
		};
	}
}

#endif