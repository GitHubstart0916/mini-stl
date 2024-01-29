#ifndef _TOY_STL_CONSTRUCT_
#define _TOY_STL_CONSTRUCT_
#include <new>
#include "toy_type_traits.h"
template <class _T1, class _T2>
inline void construct(_T1 *p, const _T2& val) {
    new (p) _T1(val);
}

template <class _T1>
inline void construct(_T1 *p) {
    new (p) _T1();
}

template <class _T1>
inline void destroy(_T1* p) {
    p->_T1::~_T1();
}

//todo: iterator need
template<class _ForwardIterator, class _T>
inline void _destroy(_ForwardIterator first, _ForwardIterator last, _T*) {
    // toy_std::is_void<_T>::value;
}

template<class _ForwardIterator> 
inline void destroy(_ForwardIterator first, _ForwardIterator last) {

}

template<> inline void destroy(char* , char*) { }

#endif