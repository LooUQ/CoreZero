//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include "CppUnitTest.h"
#include <string>

#include <CoreZero.Delegate.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreZero
{
	int plus3(int passedArg)
	{
		Logger::WriteMessage("Trace: $fntest\n");
		Logger::WriteMessage("Passed Arg: ");
		Logger::WriteMessage(std::to_string(passedArg).c_str());
		Logger::WriteMessage("\n");
		return passedArg + 3;
	}

	TEST_CLASS(Delegate_tests)
	{
	public:

		TEST_METHOD(construct_and_call)
		{			
			Delegate<decltype(plus3)> test_del = { plus3 };
			Assert::AreEqual(10, test_del(7));
		}

		TEST_METHOD(copy_and_call)
		{
			Delegate<decltype(plus3)> test_del = { plus3 };
			Delegate<decltype(plus3)> test_del2 = test_del;
			Assert::AreEqual(12, test_del2(9));
		}
	};

	TEST_CLASS(MemberDelegate_tests)
	{
		int member_integer = 0;

		int memtest(int passedArg)
		{
			Logger::WriteMessage("Trace: $fntest\n");
			Logger::WriteMessage("Passed Arg: ");
			Logger::WriteMessage(std::to_string(passedArg).c_str());
			Logger::WriteMessage("\n");
			member_integer += 5;
			return passedArg + member_integer;
		}

	public:
		TEST_METHOD(construct_and_call)
		{
			Delegate<decltype(&MemberDelegate_tests::memtest)> test_del = { this, &MemberDelegate_tests::memtest };

			Assert::AreEqual(7, memtest(2));
			Assert::AreEqual(5, member_integer);
			member_integer = 0;
		}

		TEST_METHOD(copy_and_call)
		{
			Delegate<decltype(&MemberDelegate_tests::memtest)> test_del = { this, &MemberDelegate_tests::memtest };
			Delegate<decltype(&MemberDelegate_tests::memtest)> test_del2 = test_del;

			Assert::AreEqual(8, memtest(3));
			Assert::AreEqual(5, member_integer);
			member_integer = 0;
		}

		TEST_METHOD(polymorph_delegation)
		{
			/* The delegate can be typed by a free function, and can therefore
			 * point to a member delegate that accepts the same arguments and
			 * returns the same result, but can be a member function. The
			 * $Create_MemberDelegate function abstracts the object that
			 * implements the method, from the usage of the method.
			 */
			Delegate<decltype(plus3)>* ptest_del = Create_MemberDelegate(
				this,
				&MemberDelegate_tests::memtest
			);

			Assert::AreEqual(12, (*ptest_del)(7));
			Assert::AreEqual(5, member_integer);
			member_integer = 0;
		}
	};
}
