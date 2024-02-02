#ifndef __STL_EXCEPTION_H_
#define __STL_EXCEPTION_H_


#include "stl_config.h"

class _Exception {
public:
    virtual ~_Exception() __STL_NOTHROW {}
    virtual const char* what() const __STL_NOTHROW { return ""; }
};

#define __STL_EXCEPTION_BASE _Exception



#endif