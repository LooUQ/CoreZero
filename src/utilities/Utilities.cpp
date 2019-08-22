#include "Utilities.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>



int sretreive_args(const char* str, const char * format, ...)
{
	if (str == nullptr) return -1;
	int result;

	va_list args;
	va_start(args, format);
	result = vsscanf(str, format, args);
	va_end(args);

	return result; 
}



size_t snrepl_strchr(char* str, char replChar, char subChar, size_t strLen)
{
	size_t ch = 0;
	for (; ch < strLen; ch++)
	{
		if (str[ch] == replChar)
			str[ch] = subChar;
	}
	return ch;
}
