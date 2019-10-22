#ifndef COREZERO_UTILITY_AT_DEFS_H_
#define COREZERO_UTILITY_AT_DEFS_H_

#include <stddef.h>

namespace corezero
{
	namespace utility
	{
		template <bool VERBOSE> struct ATResponseCode;
		template<> struct ATResponseCode<false>
		{
			enum
			{
				atOk = 0,
				atError = 4
			};
		};

		template<> struct ATResponseCode<true>
		{
			static constexpr const char atOK[] = "OK";
			static constexpr const char atERROR[] = "ERROR";
		};

		constexpr const char AT_Header[] = "AT";
		constexpr const char AT_WriteOp = '=';
		constexpr const char AT_ReadOp = '?';
		constexpr const char AT_TestOp[] = "=?";
		constexpr const size_t AT_MaxCommandLen = 0x70;
	}
}

#endif // !COREZERO_UTILITY_AT_DEFS_H_

