#include "CppUnitTest.h"
#include <string>

#include <CoreZero.Delegate.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreZero
{
	void fntest(int passedArg)
	{
		Logger::WriteMessage("Trace: $fntest\n");
		Logger::WriteMessage("Passed Arg: ");
		Logger::WriteMessage(std::to_string(passedArg).c_str());
		Logger::WriteMessage("\n");
	}

	TEST_CLASS(Delegate_tests)
	{
	public:

		TEST_METHOD(construct_and_call)
		{			
			Delegate<void(int)> test_del = { fntest };
			test_del(7);
		}

		TEST_METHOD(copy_and_call)
		{
			Delegate<void(int)> test_del = { fntest };
			Delegate<void(int)> test_del2 = test_del;
			test_del2(9);
		}
	};
}
