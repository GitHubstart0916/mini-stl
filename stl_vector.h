#ifndef _STL_VECTOR_H_
#define _STL_VECTOR_H_

#include "stl_alloc.h"
#include "stl_uninitialized.h"
#include "stl_config.h"
#include <cstddef>
namespace miniSTL {
    template<class _T, class _Alloc>
    class _vector_base {
        public:
            typedef _Alloc allocator_type;
            allocator_type get_allocator() const {
                return allocator_type();
            }
            _vector_base(const _Alloc&) : 
            __M_start(0), __M_finish(0), __M_end_of_storage(0) {}

            _vector_base(size_t __n, const _Alloc&) : 
            __M_start(0), __M_finish(0), __M_end_of_storage(0) {
                __M_start = _M_allocate(__n);
                __M_finish = __M_start;
                __M_end_of_storage = __M_start + __n;
            }

            ~_vector_base() {
                _M_deallocate(__M_start, __M_end_of_storage - __M_start);
            }
            
        protected:
            _T* __M_start;
            _T* __M_finish;
            _T* __M_end_of_storage;
            typedef simple_alloc<_T, _Alloc> _M_data_allocator;

            _T* _M_allocate(size_t __n) {
                return _M_data_allocator::allocate(__n);
            }
            void _M_deallocate(_T* __p, size_t __n) {
                _M_data_allocator::deallocate(__p, __n);
            }
    };

    template<class _T, class _Alloc = alloc> 
    class vector : _vector_base<_T, _Alloc> {
        private:
            typedef _vector_base<_T, _Alloc> _Base;
        public:
            typedef _T value_type;
            typedef _T* pointer;
            typedef const _T* const_pointer;
            typedef _T& reference;
            typedef const _T& const_reference;
            typedef _T* iterator;
            typedef const _T* const_iterator;

            typedef size_t size_type;
            typedef ptrdiff_t difference_type;
        
            typedef typename _Base::allocator_type allocator_type;
            allocator_type get_allocator() const {
                return allocator_type();
            }
        
        protected:


        public:
            //method
            // base method for iterator bound
            iterator begin() { return _Base::__M_start; }
            const_iterator begin() const { return _Base::__M_start; }
            iterator end() { return _Base::__M_finish; }
            const_iterator end() const { return _Base::__M_finish; }
            iterator rbegin() { return _Base::__M_finish; }
            const_iterator rbegin() const { return _Base::__M_finish; }
            iterator rend() { return _Base::__M_start; }
            const_iterator rend() const { return _Base::__M_start; }

            // continer size related method
            size_type size() const { return size_type(end() - begin()); }
            size_type max_size() const { return size_type(-1) / sizeof(value_type); }
            size_type capacity() const { return size_type(_Base::__M_end_of_storage - begin()); }
            bool empty() const { return begin() == end(); }

            // refer
            reference operator[](size_type __n) {
                return *(begin() + __n);
            }

            reference operator[](size_type __n) const {
                return *(begin() + __n);
            }

            // at
            void _M_range_check(size_type __n) {
                if (__n >= size()) __STL_RETHROW;
            }
            reference at(size_type __n) {
                
                return *(begin() + __n);
            }

    };



}





#endif