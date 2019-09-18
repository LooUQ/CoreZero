#ifndef COREZERO_ASYNC_H_
#define COREZERO_ASYNC_H_

namespace CoreZero
{
	template <typename T>
	class Async;
}





namespace CoreZero
{
	template<>
	class Async<void>
	{
	public:
		template <typename LAMBDATy_>
		auto Then(const LAMBDATy_& lambda_fn) -> Async<decltype(lambda_fn())>
		{
			Async<decltype(lambda_fn())> result;

			return result;
		}
	};


	template<typename RESULTTy_>
	class Async
	{
	public:
		Async() {}
		//Async(const Async to_copy) {}
		//Async(const Async&& to_move) {}
		virtual ~Async() {}


	public:
		template <typename LAMBDATy_>
		auto Then(const LAMBDATy_& lambda_fn) -> Async<decltype(lambda_fn())>
		{
			Async<decltype(lambda_fn())> result;

			return result;
		}

		void Fulfill(const RESULTTy_& val)
		{

		}

		void Fulfill(RESULTTy_&& val)
		{

		}

	private:
		RESULTTy_* m_pResult = nullptr;
	};
}
#endif // !COREZERO_ASYNC_H_
