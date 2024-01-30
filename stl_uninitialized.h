#pragma once
#include "type_traits.h"
#include "stl_construct.h"
#include "algorithm.h"
#include <cstring>
/*
    uninitialized_copy:

*/

template<class _InputIter, class _ForwardIter>
inline _ForwardIter
_uninitialized_copy_aux(_InputIter __first, _InputIter __last, 
                        _ForwardIter __ret, __false_type) {
    _ForwardIter __cur = __ret;
    //TODO: add try catch macro
    for (; __first != __last; ++__first, ++__cur) {
        _Construct(&*__cur, *__first);
    }
    return __cur;
}
template<class _InputIter, class _ForwardIter>
inline _ForwardIter
_uninitialized_copy_aux(_InputIter __first, _InputIter __last, 
                        _ForwardIter __ret, __true_type) {
    return copy(__first, __last, __ret);
}
template<class _InputIter, class _ForwardIter, class _T>
inline _ForwardIter
_uninitialized_copy(_InputIter __first, _InputIter __last, _ForwardIter __ret, _T*) {
    typedef typename __type_traits<_T>::is_POD_type __is_POD;
    _uninitialized_copy_aux(__first, __last, __ret, __is_POD());
}
template<class _InputIter, class _ForwardIter>
inline _ForwardIter
uninitialized_copy(_InputIter __first, _InputIter __last, _ForwardIter __ret) {
    return _uninitialized_copy(__first, __last, __ret, __VALUE_TYPE(__ret));
}
// specialize on <const chat*, char*>
template<>
inline char* uninitialized_copy<const char*, char*>(const char* __first,
                                                    const char* __last,
                                                    char* __ret)
{
    memmove(__ret, __first, __last - __first);
    return __ret + (__last - __first);
}




/*
    uninitialize_fill:

*/

template<class _ForwardIter, class _T>
inline void _uninitialized_fill_aux(_ForwardIter __first, _ForwardIter __last, 
                                const _T& __val, __true_type)
{
    file(__first, __last, __val);
}
template<class _ForwardIter, class _T>
inline void _uninitialized_fill_aux(_ForwardIter __first, _ForwardIter __last, 
                                const _T& __val, __false_type)
{
    _ForwardIter __cur = __first;
    for (; __cur != __last; ++__cur) {
        _Construct(&*__cur, __val);
    }
}
template<class _ForwardIter, class _T, class _T1>
inline void _uninitialized_fill(_ForwardIter __first, _ForwardIter __last, 
                                const _T& __val, _T1*)
{
    typedef typename __type_traits<_T1>::is_POD_type __is_POD;
    _uninitialized_fill_aux(__first, __last, __val, __is_POD());
}
template<class _ForwardIter, class _T>
inline void uninitialized_fill(_ForwardIter __first, _ForwardIter __last, 
                                const _T& __val)
{
    return _uninitialized_fill(__first, __last, __val, __VALUE_TYPE(__first));
}

/*
    uninitialized_fill_n:
*/
template<class _ForwardIter, class _size, class _T>
inline _ForwardIter
_uninitialized_fill_n_aux(_ForwardIter __first, _size __n, const _T& __val, __true_type) 
{
    return fill_n(__first, __n, __val);
}
template<class _ForwardIter, class _size, class _T>
inline _ForwardIter
_uninitialized_fill_n_aux(_ForwardIter __first, _size __n, const _T& __val, __false_type) 
{
    _ForwardIter __cur = __first;
    for (; __n > 0; --__n, ++__cur) {
        _Construct(__cur, __val);
    }
    return __cur;
}
template<class _ForwardIter, class _size, class _T, class _T1>
inline _ForwardIter
_uninitialized_fill_n(_ForwardIter __first, _size __n, const _T& __val, _T1*) 
{
    typedef typename __type_traits<_T1>::is_POD_type is_POD;
    return _uninitialized_fill_n_aux(__first, __n, __val, is_POD());
}
template<class _ForwardIter, class _size, class _T>
inline _ForwardIter
uninitialized_fill_n(_ForwardIter __first, _size __n, const _T& __val) 
{
    return _uninitialized_fill_n(__first, __n, __val, __VALUE_TYPE(__first));
}