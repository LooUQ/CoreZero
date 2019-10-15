//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include <gtest/gtest.h>

#include <CoreZero.Event.hpp>
#include <string>

using namespace CoreZero;

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
	using TestHandlerType = Delegate<void(int)>;

	int free_signal = 0;
	void OnSignal(int val)
	{
		//Logger::WriteMessage("Trace: $freeHandler\n");
		//Logger::WriteMessage("Passed val: ");
		//Logger::WriteMessage(std::to_string(val).c_str());
		//Logger::WriteMessage("\n");		
		free_signal = 1;
	}

	TEST(EventTest, ConstructAndFire)
	{
		//	construct event
		Event<TestHandlerType> test_event;
		//	subscribe to static/free handler
		test_event += OnSignal;
		//	fire event (issue call)
		test_event(7);
		//	assert the handler was fired
		Assert::IsTrue(free_signal);		
	}
}