#ifndef _STL_VECTOR_H_
#define _STL_VECTOR_H_

template<class _T, class _Alloc>
class _vector_base {
    public:
        typedef _Alloc allocator_type;
        allocator_type get_allocator() const {
            return allocator_type();
        }


    private:
        _T* __M_start;
        _T* __M_finish;
        

}





#endif