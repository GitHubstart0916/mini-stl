#ifndef _STL_STRING_FWD_H_
#define _STL_STRING_FWD_H_

#include "stl_config.h"
#include "char_traits.h"
__STL_BEGIN_NAMESPACE


template <class _CharT>
//TODO: complete char related function
class basic_string;


typedef basic_string<char> string;
typedef basic_string<wchar_t> wstring;

static const char* __get_c_string(const string&);

__STL_END_NAMESPACE

#endif