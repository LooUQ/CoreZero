#ifndef COREZERO_UTILITY_AT_DEFS_H_
#define COREZERO_UTILITY_AT_DEFS_H_

#include <stddef.h>

namespace CoreZero
{
	namespace Utility
	{
		constexpr const char AT_Header[] = "AT";
		constexpr const char AT_WriteOp = '=';
		constexpr const char AT_ReadOp = '?';
		constexpr const char AT_TestOp[] = "=?";
		constexpr const size_t AT_MaxCommandLen = 0x70;
	}
}


#endif // !COREZERO_UTILITY_AT_DEFS_H_

