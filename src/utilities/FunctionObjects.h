/******************************************************************************
*	Author:		Jensen Miller
*	Date:		Jul 24, 2018
*	Company:	LooUQ Inc
*
*	Description:	Function objects for use as callbacks, supporting the
*						event-driven paradigm.
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

#ifndef IOTQC_FUNCTIONOBJECT_H
#define IOTQC_FUNCTIONOBJECT_H

namespace iotq
{
	namespace utilities
	{
		/**
		 *	@brief The function object representing all functions that don't return
		 *		anything. A handle to actions.
		 */
		template <typename... ARGS>
		class VoidFunctor
		{
			typedef void(*Function_t)(ARGS...);
		public:
			VoidFunctor() : m_Function(nullptr) {}
			VoidFunctor(Function_t function_) : m_Function(function_) {}
			void operator=(Function_t function_) { m_Function = function_; }
			virtual void operator()(ARGS... params)
			{
				if (m_Function != nullptr)
					m_Function(params...);
			}
		private:
			Function_t m_Function;
		};

		template <>
		class VoidFunctor<void>
		{
		protected:
			typedef void(*voidFNvoid)(void);
		public:
			VoidFunctor() {}
			virtual void operator()(void) {}
			virtual operator voidFNvoid() {}
		};



		/**
		 *  @brief The void function object that represents an object's member function.
		 */
		template<typename T, typename... ARGS>
		class VoidFunctor<T, VoidFunctor<ARGS...>> : public VoidFunctor<ARGS...>
		{
			typedef void(T::*Function_t)(ARGS...);
			typedef void(T::*ConstFunct_t)(ARGS...) const;
		public:
			VoidFunctor(T * object_, Function_t function_) : m_Object(object_), m_MemberFunction(function_) {}
			//VoidFunctor(T* object_, ConstFunct_t function_) /*: m_Object(object_), m_MemberFunction(function_) */{}
			virtual void operator()(ARGS... params) override {
				(m_Object->*m_MemberFunction)(params...);
			}
		private:
			T * m_Object;
			Function_t m_MemberFunction;
		};

		template<typename T, typename... ARGS>
		class VoidFunctor<T(ARGS...)> : public VoidFunctor<ARGS...>
		{
			typedef void(T::*Function_t)(ARGS...);
		public:
			VoidFunctor(T * object_, Function_t function_) : m_Object(object_), m_MemberFunction(function_) {}
			//VoidFunctor(T* object_, ConstFunct_t function_) /*: m_Object(object_), m_MemberFunction(function_) */{}
			virtual void operator()(ARGS... params) override {
				(m_Object->*m_MemberFunction)(params...);
			}
		private:
			T * m_Object;
			Function_t m_MemberFunction;
		};

	}
}

namespace mbd
{
	template <typename T>
	class function;

	template <typename RET, typename... ARGS>
	class function<RET(ARGS...)>
	{
		typedef RET(*p_function_t)(ARGS...);

		//
		//	Constructors
		//
	public:
		function() = delete;
		function(p_function_t fn_) : m_function(fn_) {}
		template <typename FN> function(FN fn_) : m_function(fn_) {}

		//
		//	Operations
		//
	public:
		RET operator()(ARGS... params_) { return m_function(params_...); }

		//
		//	Attributes
		//
	private:
		const p_function_t m_function;
	};

	template <typename RET, typename T>
	class function<RET(T&)>
	{
		RET(T::* m_memberFunction)();
	public:
		function(RET(T::* memberFunction)()) : m_memberFunction(memberFunction) {}

		RET operator()(T& instance_) { return ((&instance_)->*m_memberFunction)(); }
	};
}

#endif // !IOTQC_FUNCTIONOBJECT_H
