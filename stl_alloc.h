#ifndef _STL_ALLOC_
#define _STL_ALLOC_

// prefix:
// func name:       _ 
// enum name:       __
// var name:        __
// class name:      __
// macro name:      __

#include <cstring>
#define __THROW_BAD_ALLOC fprintf(stderr, "out of memory\n"); exit(1) 

#include <cstdio>
#include <cstddef>
#include <cstdlib>
//


template<int __inst>
class __malloc_alloc_template {
    private:
        static void *_oom_malloc(size_t);
        static void *_oom_realloc(void*, size_t);
    public:
        static void (*__malloc_alloc_oom_handler)();
        static void* allocate(size_t __n) {
            void* __result = malloc(__n);
            if (__result == 0) __result = _oom_malloc(__n);
            return __result;
        }
        static void* deallocate(void* __p, size_t __n) {
            free(__p);
        }
        static void* _reallocate(void* __p, size_t __n) {
            void* __result = realloc(__p, __n);
            if (__result == 0) __result = _oom_realloc(__p, __n);
            return __result;
        }
        static void (*set_malloc_alloc_handler(void (*__f)()))() {
            void (*__old)() = __malloc_alloc_oom_handler;
            __malloc_alloc_oom_handler = __f;
            return (__old);
        }
};

//out-of-memory-handler
template <int __inst>
void (*__malloc_alloc_template<__inst>::__malloc_alloc_oom_handler)() = 0;

template<int __inst>
void*
__malloc_alloc_template<__inst>::_oom_malloc(size_t __n) {
    void (* _m_malloc_handler)();
    void* __result;

    for (; ; ) {
        _m_malloc_handler = __malloc_alloc_oom_handler;
        if (_m_malloc_handler == 0) {__THROW_BAD_ALLOC;}
        _m_malloc_handler();
        __result = malloc(__n);
        if (__result) return (__result);
    }
}

template<int __inst>
void*
__malloc_alloc_template<__inst>::_oom_realloc(void* __p, size_t __n) {
    void (* _m_realloc_handler)();
    void* __result;
    for (; ; ) {
        _m_realloc_handler = __malloc_alloc_oom_handler;
        if (_m_realloc_handler == 0) {__THROW_BAD_ALLOC;}
        _m_realloc_handler();
        __result = realloc(__p, __n);
        if (__result) return (__result);
    }
}

// first level memmory sche
typedef __malloc_alloc_template<0> malloc_alloc;

enum {__ALIGN = 8};
enum {__MAX_BYTES = 128};
enum {__NFREELISTS = 16};
template<bool __threads, int __inst>
class __default_alloc_template {
    private:
        static size_t _round_up(size_t __bytes) {
            // round up N: (x + N - 1) - (x + N - 1) % N, ie M - M % N
            // N is a power of 2, so  
            // M - M % N = M & ~(N - 1)
            return ((__bytes) + (size_t) __ALIGN - 1) & ~((size_t) __ALIGN - 1);
        }
    private:
        union _obj {
            union obj* __next_free_block;
            char __client_data[1];
        };
        // free_list block size: [8, 16, ..., 128]
        static _obj* volatile __free_list[__NFREELISTS];
        static size_t _free_list_index(size_t __bytes) {
            return (((__bytes) + (size_t) __ALIGN - 1) / (size_t) __ALIGN - 1);
        }

        static void* _refill(size_t __n);
        static char* _chunk_alloc(size_t __n, int& __nobjs);

        //chunk alloc state
        static char* __start_free;
        static char* __end_free;
        static size_t __heap_size;
    public:
        // need node at head
        static void* allocate(size_t __n) {
            void* __ret = 0;
            if (__n > (size_t) __MAX_BYTES) {
                __ret = malloc_alloc::allocate(__n);
            } else {
                _obj* volatile *__my_free_list = __free_list + _free_list_index(__n);
                _obj* __result = *__my_free_list;
                if (__my_free_list == 0) {
                    __ret = _refill(_round_up(__n));
                } else {
                    *__my_free_list = __result->__next_free_block;
                    __ret = __result;
                }
            }
            return __ret;
        }
        // link insert at head
        static void deallocate(void* __p, size_t __n) {
            if (__n > (size_t) __MAX_BYTES) {
                malloc_alloc::deallocate(__p, __n);
            } else {
                _obj* volatile* __my_free_list = __free_list + _free_list_index(__n);
                _obj* __q = (_obj*) __p;

                __q->__next_free_block = *__my_free_list;
                *__my_free_list = __q;
            }
        }
        static void* reallocate(void* __p, size_t __old_size, size_t __new_size);
};

// assume that __n is aligned with __ALIGN
template<bool __threads, int __inst>
void* __default_alloc_template<__threads, __inst>::_refill(size_t __n) {
    int __nobjs = 20;
    char* __chunk = _chunk_alloc(__n, __nobjs);
    _obj* volatile* __my_free_list;
    _obj* __result;
    _obj*  __current_obj;
    _obj* __next_obj;
    int __i;
    if (__nobjs == 1) return (__chunk);
    __my_free_list = __free_list + _free_list_index(__n);
    __result = (_obj*) __chunk;
    // use one block other insert in the free_list
    *__my_free_list = __next_obj = (_obj*)(__chunk + __n);
    for (__i = 1; ; __i++) {
        __current_obj = __next_obj;
        __next_obj = (_obj*) ((char*) __next_obj + __n);
        if (__i == __nobjs - 1) {
            __current_obj->__next_free_block = 0;
            break;
        } else {
            __current_obj->__next_free_block = __next_obj;
        }
    }
    return (__result);
}

// asume that __n is aligned
// allocate memory in large chunks in order to avoid fragmenting the malloc heap too much
template<bool __threads, int __inst>
char*
__default_alloc_template<__threads, __inst>::_chunk_alloc(size_t __n, int & __nobjs) {
    char *__ret;
    size_t __total_bytes = __n * __nobjs;
    size_t __left_bytes = __end_free - __start_free;

    if (__left_bytes >= __total_bytes) {
        __ret = __start_free;
        __start_free += __total_bytes;
        return (__ret);
    } else if (__left_bytes >= __n) {
        __nobjs = (int) (__left_bytes / __n);
        __total_bytes = __nobjs * __n;
        __ret = __start_free;
        __start_free += __total_bytes;
        return (__ret);
    } else {
        // is this a magic trick?
        size_t __to_get_bytes = 2 * __total_bytes + _round_up(__heap_size >> 4);
        if (__left_bytes > 0) {
            // use left memory, reduce but still can result in pieces of fragment
            _obj* volatile* __my_free_list = __free_list + _free_list_index(__left_bytes);

            ((_obj*) __start_free)->__next_free_block = *__my_free_list;
            *__my_free_list = (_obj*) __start_free;
        }
        __start_free = (char*) malloc(__to_get_bytes);
        if (__start_free == 0) {
            // heap memory not enough
            // use other size memory block
            size_t __i;
            _obj* volatile* __my_free_list;
            _obj* __p;
            for (__i = __n; __i <= (size_t) __MAX_BYTES; __i += (size_t) __ALIGN) {
                __my_free_list = __free_list + _free_list_index(__i);
                __p = *__my_free_list;
                if (__p != 0) {
                    *__my_free_list = __p->__next_free_block;
                    __start_free = (char*) __p;
                    __end_free = __start_free + __i;
                    return (_chunk_alloc(__n, __nobjs));
                }
            }
            __end_free = 0;
            // maybe  _oom_malloc/alloc can solve this problem
            // ie. __malloc_alloc_oom_handler
            __start_free = (char*) malloc_alloc::allocate(__to_get_bytes);

        }
        __heap_size += __to_get_bytes;
        __end_free = __start_free + __to_get_bytes;
        return (_chunk_alloc(__n, __nobjs));
    }
}

template<bool __threads, int __inst>
void*
__default_alloc_template<__threads, __inst>::reallocate(void* __p, size_t __old_size, size_t __new_size) {
    void* __ret;
    size_t __copy_size;

    if (__old_size > (size_t) __MAX_BYTES && __new_size > (size_t) __MAX_BYTES) {
        return (realloc(__p, __new_size));
    }
    if (_round_up(__new_size) == _round_up(__old_size)) return (__p);
    __ret = allocate(__new_size);
    __copy_size = __new_size > __old_size ? __old_size : __new_size;
    memcpy(__ret, __p, __copy_size);
    deallocate(__p, __old_size);
    return (__ret);
}

#endif