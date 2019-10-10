#ifndef COREZERO_UTILITY_AT_DEFS_H_
#define COREZERO_UTILITY_AT_DEFS_H_

#include <stddef.h>

namespace CoreZero
{
	namespace Utility
	{
		template <bool VERBOSE> struct AT_ResponseCode;
		template<> struct AT_ResponseCode<false>
		{
			enum
			{
				OK = 0,
				ERROR = 4
			};
		};

		template<> struct AT_ResponseCode<true>
		{
			static constexpr const char OK[] = "OK";
			static constexpr const char ERROR[] = "ERROR";
		};

		constexpr const char AT_Header[] = "AT";
		constexpr const char AT_WriteOp = '=';
		constexpr const char AT_ReadOp = '?';
		constexpr const char AT_TestOp[] = "=?";
		constexpr const size_t AT_MaxCommandLen = 0x70;
	}
}

#endif // !COREZERO_UTILITY_AT_DEFS_H_

