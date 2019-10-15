//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include <CppUnitTest.h>
#include <string>

#include <CoreZero.Async.h>
using namespace CoreZero;

#include <thread>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreZero
{
	void plus_5(Async::Request<int>&& request)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		request.Fulfill(5);
	}

	TEST_CLASS(Async_tests)
	{
	public:
		TEST_METHOD(basic_with_copies)
		{
			Async::Request<int> async_req;
			Async::Result<int> async_result = async_req.GetAsyncResult();

			std::thread th(plus_5, async_req);

			int xplus5 = await async_result;
			Assert::AreEqual(5, xplus5);
			th.join();
		}


		TEST_METHOD(chaining_with_copies)
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

	};
}