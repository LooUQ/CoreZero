/******************************************************************************
*	\file	CoreZero.Async.hpp
*
*	\author	Jensen Miller	<jensen@loouq.com>
*
*	Copyright (c) 2018 LooUQ Incorporated
*
*	License: The GNU Licence(GNU)
*
*	This file is part of the CoreZero library.
*
*	CoreZero is free software: you can redistribute it and/or modify
*	it under the terms of the GNU General Public License as published by
*	the Free Software Foundation, either version 3 of the License, or
*	(at your option) any later version.
*
*	CoreZero is distributed in the hope that it will be useful,
*	but WITHOUT ANY WARRANTY; without even the implied warranty of
*	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*	GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License
*	along with CoreZero.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/
#ifndef COREZERO_ASYNC_H_
#define COREZERO_ASYNC_H_

#include "CoreZero.Event.hpp"
#include <signal.h>


#define await !


namespace CoreZero
{
	template <typename>
	class Async;

	template <typename>
	class Request;

	template <typename>
	class AsyncTask;
}





namespace CoreZero
{
	template <typename RESULTTy_>
	RESULTTy_ operator await (const Async<RESULTTy_>& asyncResult);


	template<>
	class Async<void>
	{
		friend Request<void>;
	public:
		template <typename LAMBDATy_>
		auto Then(const LAMBDATy_& lambda_fn) -> Async<decltype(lambda_fn())>
		{
			Async<decltype(lambda_fn())> result;

			return result;
		}

	private:
		void set()
		{

		}
	};



	template<typename RESULTTy_>
	class Async
	{
		friend Request<RESULTTy_>;
		RESULTTy_ friend CoreZero::operator await (const Async<RESULTTy_>&);

	//
	//	Constructors & Assignments
	//
	private:
		/* Constructor. */
		Async(Request<RESULTTy_> * request)
			: m_hasOwnership(true)
		{
			m_pResult = new RESULTTy_();	// Must be default-constructable
			m_pPending = new volatile bool(true);
		}

	public:

		/* Copy constructor. Only pointers, no need for move. */
		Async(const Async& to_copy)
			: m_pResult(to_copy.m_pResult)
			, m_pPending(to_copy.m_pPending)
		{}



		/* Destructor. Destruct if this Async object owns pointers. */
		virtual ~Async()
		{
			if (m_hasOwnership)
			{
				delete m_pResult;
				delete m_pPending;
			}
		}


	//
	//	Methods
	//
	public:

		template <typename LAMBDATy_>
		inline auto Then(const LAMBDATy_& lambda_fn) -> Async<decltype(lambda_fn(RESULTTy_()))>
		{			
			AsyncTask<decltype(lambda_fn(RESULTTy_()/* Must be default-constructable */))(RESULTTy_)> chain_task(
				Create_MemberDelegate
				(
					lambda_fn,
					&LAMBDATy_::operator()
				)
			);

			//m_pChainHandling = Create_MemberDelegate(&chain_task, &decltype(chain_task)::operator());

			return chain_task.GetAsyncResult();
		}

	private:
		void set_result(const RESULTTy_& result)
		{
			(*m_pResult) = result;
			(*m_pPending) = false;			
			(m_pChainHandling == nullptr) ? NULL : (*m_pChainHandling)(*m_pResult);
		}
		

	//
	//	Attributes
	//
	private:
		/// Wether this object owns the dynamic pointers.
		bool m_hasOwnership = false;

		/// The location of the result.
		RESULTTy_* m_pResult = nullptr;

		/// Wether this object is still awaiting the result.
		volatile bool* m_pPending = nullptr;

	private:
		Delegate<void(RESULTTy_)>* m_pChainHandling = nullptr;
	};


	/*
	*/
	template <typename RESULTTy_>
	RESULTTy_ operator await (const Async<RESULTTy_>& asyncResult)
	{
		// wait_for_interrupt
		while (*asyncResult.m_pPending)
			;
		return *asyncResult.m_pResult;
	}





	template <>
	class Request<void>
	{
	public:
		Request() {}
		virtual ~Request() {}

		inline Async<void> GetAsyncResult() const
		{
			return m_asyncResult;
		}

		void Fulfill(void)
		{
			m_asyncResult.set();
		}

	private:
		Async<void> m_asyncResult;
	};



	template <typename RESULTTy_>
	class Request
	{
	public:
		Request()
			: m_asyncResult(this)
		{}

		Request(const Request& copy_request)
			: m_asyncResult(copy_request.m_asyncResult)
		{}


		virtual ~Request() {}

		inline Async<RESULTTy_> GetAsyncResult() const
		{
			return m_asyncResult;
		}



		void Fulfill(const RESULTTy_& result)
		{
			m_asyncResult.set_result(result);
		}

	private:
		Async<RESULTTy_> m_asyncResult;
	};





	template <typename RESULTTy_, typename ... ARGS>
	class AsyncTask<RESULTTy_(ARGS...)>		
	{
	public:
		using result_type = RESULTTy_;
		using fn_type = RESULTTy_(*)(ARGS...);

	public:
		AsyncTask() = delete;
		AsyncTask(const AsyncTask& copy_task)
			: m_request(copy_task.m_request)
			, m_task(copy_task.m_task)
		{}


		AsyncTask(const fn_type fn_)
		{
			m_task = new Delegate<RESULTTy_(ARGS...)>{ fn_ };
		}

		AsyncTask(Delegate<RESULTTy_(ARGS...)>* taskDelegate)
		{
			m_task = taskDelegate;
		}

		inline Async<RESULTTy_> GetAsyncResult() const
		{
			return m_request.GetAsyncResult();
		}

		inline void operator()(void)
		{
			m_request.Fulfill();
		}

		inline void operator()(ARGS... args_)
		{
			m_request.Fulfill((*m_task)(args_...));
		}

	private:
		Request<RESULTTy_> m_request;
		Delegate<RESULTTy_(ARGS...)>* m_task = nullptr;
	};
}
#endif // !COREZERO_ASYNC_H_
