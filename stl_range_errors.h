#ifndef _STL_RANGE_ERRORS_H_
#define _STL_RANGE_ERRORS_H_

#include "stdexcept"
#include "stl_config.h"
__STL_BEGIN_NAMESPACE


inline void _stl_throw_range_error(const char* __msg) {
    throw;
}

inline void _stl_throw_length_error(const char* __msg) {
    throw;
}

__STL_END_NAMESPACE

#endif