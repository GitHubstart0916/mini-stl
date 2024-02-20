#ifndef _TOY_STL_CONSTRUCT_
#define _TOY_STL_CONSTRUCT_
#include <new>
#include "type_traits.h"
template <class _T1, class _T2>
inline void _Construct(_T1 *__p, const _T2& __val) {
    new ((void*) __p) _T1(__val);
}

template <class _T1>
inline void _Construct(_T1 *__p) {
    new ((void*) __p) _T1();
}

template <class _T1>
inline void _Destroy(_T1* __p) {
    __p->~_T1();
}

template<class _ForwardIterator>
void
_destory_aux(_ForwardIterator __first, _ForwardIterator __last, __false_type) {
    for (; __first != __last; ++__first)
        destroy(&*__first);
}

template<class _ForwardIterator>
void
_destory_aux(_ForwardIterator __first, _ForwardIterator __last, __true_type) {}

//todo: iterator need
template<class _ForwardIterator, class _T>
inline void _destroy(_ForwardIterator __first, _ForwardIterator __last, _T*) {
    // toy_std::is_void<_T>::value;
    typedef typename __type_traits<_T>::has_trivial_destructor __Trivial_destructor;
    _destory_aux(__first, __last, __Trivial_destructor());
}

template<class _ForwardIterator> 
inline void _Destroy(_ForwardIterator first, _ForwardIterator last) {
    _destroy(first, last, __VALUE_TYPE(first));
}



template<> inline void _Destroy(char* , char*) { }
template<> inline void _Destroy(int* , int*) { }
template<> inline void _Destroy(long* , long*) { }
template<> inline void _Destroy(float* , float*) { }
template<> inline void _Destroy(double* , double*) { }

#endif