//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include <gtest/gtest.h>

#include <CoreZero.Async.h>
#include <string>
#include <thread>

//	Aliases for Google Tests <-> Microsoft UnitTest Framework
namespace Assert
{
	template <typename T>
	inline void AreEqual(T val1, T val2)
	{
		ASSERT_EQ(val1, val2);
	}

	inline void IsTrue(bool _expectedTrue)
	{
		ASSERT_TRUE(_expectedTrue);
	}
}


namespace CoreZero
{
	void plus_5(Async::Request<int>&& request)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		request.Fulfill(5);
	}

	TEST(AsyncTest, ConstructAndCopy)
	{
		Async::Request<int> async_req;
		Async::Result<int> async_result = async_req.GetAsyncResult();

		std::thread th(plus_5, async_req);

		int xplus5 = await async_result;
		Assert::AreEqual(5, xplus5);
		th.join();
	}

	TEST(AsyncTest, ChainingWithCopies)
	{
		Async::Request<int> async_req;
		Async::Result<int> async_result = async_req.GetAsyncResult();

		async_result.Then([](int xplus5)
			{
				Assert::AreEqual(5, xplus5);
			});

		std::thread th(plus_5, async_req);

		th.join();
	}
}