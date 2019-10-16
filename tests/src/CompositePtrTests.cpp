//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include <gtest/gtest.h>
#include <corezero/memory/composite_pointer.h>

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


namespace corezero
{
	namespace memory
	{
		TEST(CompositePtrTest, NullConstruction)
		{
			CompositePtr<unsigned> pID = { nullptr };
			Assert::AreEqual((void*)nullptr, (void*)pID.get());
		}

		TEST(CompositePtrTest, AcceptDynamicAllocation)
		{
			CompositePtr<unsigned> pID = new unsigned(7U);
			Assert::AreEqual(7U, *pID);
		}

		TEST(CompositePtrTest, ManipulatePointersValue)
		{
			CompositePtr<unsigned> pID = new unsigned(9U);
			*pID = 11U;
			Assert::AreEqual(11U, *pID);
		}

		class MyTestComponent
		{
		public:
			MyTestComponent() {}
			~MyTestComponent() {}

		public:
			bool ReturnTrue() const { return true; }
			bool ReturnFalse() const { return false; }
		};

		TEST(CompositePtrTest, SampleComponent)
		{
			CompositePtr<MyTestComponent> c_test_component = new MyTestComponent;
			Assert::IsTrue(c_test_component->ReturnTrue());
			Assert::IsTrue(!c_test_component->ReturnFalse());
		}
	}
}