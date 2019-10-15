//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include "CppUnitTest.h"
#include <string>

#include <CoreZero.Event.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreZero
{
	using TestHandlerType = Delegate<void(int)>;

	int freeSignal = 0;
	void freeHandler(int val)
	{
		Logger::WriteMessage("Trace: $freeHandler\n");
		Logger::WriteMessage("Passed val: ");
		Logger::WriteMessage(std::to_string(val).c_str());
		Logger::WriteMessage("\n");		
		freeSignal = 1;
	}

	TEST_CLASS(Event_tests)
	{
	public:

		TEST_METHOD(construct_and_trigger)
		{
			Event<TestHandlerType> test_ev;
			test_ev += freeHandler;
			test_ev(7);
			Assert::IsTrue(freeSignal);
			freeSignal = 0;
		}
	};
}