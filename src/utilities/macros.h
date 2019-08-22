#pragma once

#ifndef LOOUQ_MACROS_H
#define LOOUQ_MACROS_H


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


// Delete default constructors.
#define DeleteDefaults(CLASS_NAME)\
public:\
CLASS_NAME() = delete;\
CLASS_NAME(const CLASS_NAME&) = delete;\
CLASS_NAME(CLASS_NAME&&) = delete

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // !LOOUQ_MACROS_H