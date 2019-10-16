//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include <gtest/gtest.h>
#include <corezero/delegate.hpp>

#include <string>



//	Aliases for Google Tests <-> Microsoft UnitTest Framework
namespace Assert
{
	template <typename T>
	void AreEqual(T val1, T val2)
	{
		ASSERT_EQ(val1, val2);
	}
}


namespace corezero
{
	namespace tests
	{
		/**	Add 3 to a provided argument and return the result.
		 *	\param[in] passedArg The integer to increment by 3.
		 */
		int plus3(int passedArg)
		{
			//Logger::WriteMessage("Trace: $fntest\n");
			//Logger::WriteMessage("Passed Arg: ");
			//Logger::WriteMessage(std::to_string(passedArg).c_str());
			//Logger::WriteMessage("\n");
			std::cerr << "Passed Argument: %d" << passedArg << std::endl;
			return passedArg + 3;
		}



		TEST(DelegateTest, ConstructAndCall)
		{
			//	create delegate
			Delegate<decltype(plus3)> test_del = { plus3 };
			//	call delegate
			Assert::AreEqual(10, test_del(7));			
		}



		TEST(DelegateTest, CopyAndCall)
		{
			//	create delegate
			Delegate<decltype(plus3)> test_del = { plus3 };
			//	copy delegate
			Delegate<decltype(plus3)> test_del2 = test_del;
			//	ensure equivalent operation
			Assert::AreEqual(test_del(9), test_del2(9));
		}





// ----------------------------------------------------------------------------
//		Member Delegate Testing 
// ----------------------------------------------------------------------------

		class MemberDelegateTest
			: public ::testing::Test
		{
		public:
			/** Perform default aggregation */
			void SetUp() override
			{

			}

			/**	Clean up MemberDelegateTest's dynamic data */
			void TearDown() override
			{

			}

			/**	Increment an member variable by a provided integer.
			 *	\param[in] passedArg The integer to add to the member variable.
			 */
			void IncrementVariableBy(int passedArg)
			{
				//Logger::WriteMessage("Trace: $fntest\n");
				//Logger::WriteMessage("Passed Arg: ");
				//Logger::WriteMessage(std::to_string(passedArg).c_str());
				//Logger::WriteMessage("\n");
				member_variable += passedArg;
			}

			int member_variable = 0;
		};



		TEST_F(MemberDelegateTest, ConstructAndCall)
		{
			Delegate<decltype(&MemberDelegateTest::IncrementVariableBy)> test_del = { this, &MemberDelegateTest::IncrementVariableBy };

			//	increment member variable via delegate
			test_del(2);
			Assert::AreEqual(2, member_variable);
			test_del(5);
			Assert::AreEqual(7, member_variable);			
		}



		TEST_F(MemberDelegateTest, CopyAndCall)
		{
			Delegate<decltype(&MemberDelegateTest::IncrementVariableBy)> test_del = { this, &MemberDelegateTest::IncrementVariableBy };
			Delegate<decltype(&MemberDelegateTest::IncrementVariableBy)> test_del2 = test_del;

			test_del2(5);
			Assert::AreEqual(5, member_variable);
			test_del(6);
			Assert::AreEqual(11, member_variable);			
		}



		void increment_by_dummy(int) {}

		/**	Polymorphic Delegation Test
		 *
		 *	The delegate can be typed by a free function, and can therefore
		 * point to a member delegate that accepts the same arguments and
		 * returns the same result, but can be a member function. The
		 * $Create_MemberDelegate function abstracts the object that
		 * implements the method, from the usage of the method.
		 */
		TEST_F(MemberDelegateTest, PolymorphicDelegation)
		{
			//	A non-member delegate pointer is instantiated with a 
			//		dynamic member delegate.
			Delegate<decltype(increment_by_dummy)>* p_test_delegate = Create_MemberDelegate(
				(MemberDelegateTest * const)this,
				&MemberDelegateTest::IncrementVariableBy
			);

			//	increment member variable and check it
			(*p_test_delegate)(7);
			Assert::AreEqual(7, member_variable);
			(*p_test_delegate)(9);
			Assert::AreEqual(16, member_variable);			
		}
	}
}
