//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include <gtest/gtest.h>

#include <CoreZero.Event.hpp>
#include <string>


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

	/** Events are typically get constructed in classes
	 *	however, they aren't always subscribed to. Thus
	 *	we need to test an unsubscribed event for 
	 *	being fired with the possiblity of no subscriber
	 *	and NOT throw an exception*/
	TEST(EventTest, ConstructUnsubscribed)
	{
		Event<TestHandlerType> test_event;
		test_event(7);
		//	Nothing should happen
		//		Events should be constructable
		//		without being aggregated and
		//		not throw an error.
		SUCCEED();
	}


	/// A free signal variable for checking.
	int free_signal = 0;

	/** The method to execute on a given signal.
	 *	\param[in] val An argument to pass to the handler. */
	void OnSignal(int val)
	{
		//Logger::WriteMessage("Trace: $freeHandler\n");
		//Logger::WriteMessage("Passed val: ");
		//Logger::WriteMessage(std::to_string(val).c_str());
		//Logger::WriteMessage("\n");		
		free_signal = 1;
	}



	/**	Typical usage of an event includes a subscriber method
	 *	that gets called upon a signal. This is a uni-directional
	 *	signal, in which one object signals another object or method. */
	TEST(EventTest, SubscribeAndFire)
	{
		//	construct event
		Event<TestHandlerType> something_signaled;
		//	subscribe to static/free handler
		something_signaled += OnSignal;
		//	fire event (issue call)
		something_signaled(7);
		//	assert the handler was fired
		Assert::IsTrue(free_signal);		
	}

	using Accumulator = Delegate<int(int, int)>;

	/** Sum two integers.
	 *	\param[in] x An integer.
	 *	\param[in] y An integer. */
	int Sum(int x, int y)
	{
		return x + y;
	}

	/** Alternatively, events can be used for bi-directional signaling, where
	 *	the signaler can pass data to the subscriber, and the subscriber can
	 *	return a value to the event without knowing who the event belongs to. */
	TEST(EventTest, EventWithReturingSubscriber)
	{
		//	construct event
		Event<Accumulator> accumulating_event;
		//	subscribe
		accumulating_event += Sum;
		//	check the RETURN value of the subscriber method
		Assert::AreEqual(12, accumulating_event(5, 7));
	}


	//	\TODO: Test Event with MemberDelegate
}