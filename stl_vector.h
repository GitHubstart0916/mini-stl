#ifndef _STL_VECTOR_H_
#define _STL_VECTOR_H_

#include "stl_alloc.h"
template<class _T, class _Alloc>
class _vector_base {
    public:
        typedef _Alloc allocator_type;
        allocator_type get_allocator() const {
            return allocator_type();
        }
        
    protected:
        _T* __M_start;
        _T* __M_finish;
        _T* __M_end_of_storage;
        typedef simple_alloc<_T, _Alloc> _M_data_allocator;

};





#endif