#pragma once


#include <string.h>
#include <stdlib.h>

#ifndef IOTQC_CUTILITIES_H
#define IOTQC_CUTILITIES_H

#define NULLSTR "<nullstr>"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

	int sretreive_args(const char* str, const char * format, ...);

	size_t snrepl_strchr(char* str, char repl, char sub, size_t strLen);

	size_t memextend(void * ptr, size_t size);

#ifdef __cplusplus
}
#endif // __cplusplus


#ifdef __cplusplus

	template <typename T>
	inline T* Renew(T* &loc)
	{
		loc->~T();
		return new (loc) T;
	}

	template<typename T>
	void Invalidate(T* &T_ptr)
	{
		T_ptr = nullptr;
	}
	
	template<typename T>
	void Dispose(T* &T_ptr)
	{
		if (T_ptr != nullptr) delete T_ptr;
		Invalidate(T_ptr);
	}


	template<typename T>
	void SwapOwnership(T* &ptr1, T* &ptr2)
	{

	}

	template<typename T, typename V>
	void Renew(T* T_ptr, V& T_val)
	{
		Dispose(T_ptr);
		T_ptr = new T(T_val);
	}

	template<typename T>
	T* memextend(T* ptr, size_t newSize)
	{
		T* temp = nullptr;
		if ((temp = (T*)realloc(ptr, newSize * sizeof(T))) != nullptr) {
			return temp;
		}
		else
		{
			delete ptr;
			return new T[newSize];
		}
	}

#endif



#endif // !IOTQC_CUTILITIES_H
