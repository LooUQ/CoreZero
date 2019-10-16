//	Copyright (c) 2019 LooUQ Incorporated.

//	Licensed under the GNU GPLv3. See LICENSE file in the project root for full license information.
#include <gtest/gtest.h>
#include <corezero/string.hpp>



//	Aliases for Google Tests <-> Microsoft UnitTest Framework
namespace Assert
{
	template <typename T>
	inline void AreEqual(T val1, T val2)
	{
		ASSERT_EQ(val1, val2);
	}


	template<>
	inline void AreEqual<const char*>(const char* val1, const char* val2)
	{
		ASSERT_STREQ(val1, val2);
	}

	inline void IsTrue(bool _expectedTrue)
	{
		ASSERT_TRUE(_expectedTrue);
	}
}


namespace corezero
{
	TEST(StringTest, ConstructEmpty)
	{
		String _string;
		Assert::AreEqual(0U, _string.GetLength());
	}

	TEST(StringTest, ConstructFromCString)
	{
		String _string("Hello World");
		Assert::AreEqual(11U, _string.GetLength());
		Assert::AreEqual("Hello World", _string.c_str());
	}

	TEST(StringTest, Concatenation)
	{
		String _string;
		_string += "Hello";
		Assert::AreEqual(5U, _string.GetLength());
		Assert::AreEqual("Hello", _string.c_str());
		_string += ' ';
		_string += "World";
		Assert::AreEqual(11U, _string.GetLength());
		Assert::AreEqual("Hello World", _string.c_str());
	}
}
