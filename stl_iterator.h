#ifndef _STL_ITERATOR_
#define _STL_ITERATOR_

#include<cstddef>
// iterator types:
struct input_iterator_tag {}; //read only
struct output_iterator_tag {}; // write only
struct forward_iterator_tag : input_iterator_tag {}; //read & write
struct bidirectional_iterator_tag : forward_iterator_tag {}; // operator-- && operator++
struct random_access_iterator_tag : bidirectional_iterator_tag {}; // p+n, p-n, etc.

// iterator_catepory, value_type, difference_type, pointer, reference
template<class _Iter, class _T, 
        class _Dis = ptrdiff_t, class _Pointer = _T*, class _Reference = _T&>
struct iterator {
    typedef _Iter           iterator_category;
    typedef _T              value_type;
    typedef _Dis            difference_type;
    typedef _Pointer        pointer;
    typedef _Reference      reference;
};

template<class _T>
struct iterator_traits {
    typedef typename _T::iterator_category      iterator_category;
    typedef typename _T::value_type             value_type;
    typedef typename _T::difference_type        difference_type;
    typedef typename _T::pointer                pointer;
    typedef typename _T::reference              reference;
};

template<class _T>
struct iterator_traits<_T*> {
    typedef random_access_iterator_tag      iterator_category;
    typedef _T                              value_type;
    typedef ptrdiff_t                       difference_type;
    typedef _T*                             pointer;
    typedef _T&                             reference;
};

template<class _T>
struct iterator_traits<const _T*> {
    typedef random_access_iterator_tag      iterator_category;
    typedef _T                              value_type;
    typedef ptrdiff_t                       difference_type;
    typedef const _T*                       pointer;
    typedef const _T&                       reference;
};

template<class _Iter>
inline typename iterator_traits<_Iter>::iterator_category
__iterator_category(const _Iter&) {
    typedef typename iterator_traits<_Iter>::iterator_category _Category;
    return _Category();
}
template<class _Iter>
inline typename iterator_traits<_Iter>::value_type
__value_type(const _Iter&) {
    typedef typename iterator_traits<_Iter>::value_type _T;
    return _T();
}
template<class _Iter>
inline typename iterator_traits<_Iter>::difference_type
__difference_type(const _Iter&) {
    typedef typename iterator_traits<_Iter>::difference_type _Dis;
    return _Dis();
}


template<class _Iter>
inline typename iterator_traits<_Iter>::iterator_category
iterator_category(const _Iter& __i) {
    return __iterator_category(__i);
}
template<class _Iter>
inline typename iterator_traits<_Iter>::value_type
value_type(const _Iter& __i) {
    return __value_type(__i);
}
template<class _Iter>
inline typename iterator_traits<_Iter>::difference_type
difference_type(const _Iter& __i) {
    return __difference_type(__i);
}
#define __ITERATOR_CATEGORY(__i)    __iterator_category(__i)
#define __DISTANCE_TYPE(__i)        __distance_type(__i)
#define __VALUE_TYPE(__i)           __value_type(__i)

// distance
// use internal
template<class _InputIterator>
inline typename iterator_traits<_InputIterator>::difference_type
__distance(_InputIterator __first, _InputIterator __last, 
            input_iterator_tag) {
    typename iterator_traits<_InputIterator>::difference_type __i = 0;
    for (; __first != __last; ++__i, ++__last) {}
    return __i;
}
template<class _InputIterator>
inline typename iterator_traits<_InputIterator>::difference_type
__distance(_InputIterator __first, _InputIterator __last, 
            random_access_iterator_tag) {
    typename iterator_traits<_InputIterator>::difference_type __i = 0;
    // for (; __first != __last; ++__i, ++__last) {}
    return __last - __first;
}
//use external
template<class _InputIterator>
inline typename iterator_traits<_InputIterator>::difference_type
distance(_InputIterator __first, _InputIterator __last) {
    typedef typename iterator_traits<_InputIterator>::iterator_category _Category;
    return __distance(__first, __last, _Category());
}


// advance
// use internal
template<class _InputIterator, class _Distance>
inline void
__advance(_InputIterator& __first, _Distance __n, 
            input_iterator_tag) {
    while (__n--) __first++;
}
template<class _InputIterator, class _Distance>
inline void
__advance(_InputIterator& __first, _Distance __n, 
            bidirectional_iterator_tag) {
    if (__n > 0)
        while (__n--) __first++;
    else 
        while (__n++) __first--;
}
template<class _InputIterator, class _Distance>
inline void
__advance(_InputIterator& __first, _Distance __n, 
            random_access_iterator_tag) {
    __first += __n;
}
// use external
template<class _InputIterator, class _Distance>
inline void
advance(_InputIterator& __p, _Distance __n) {
    typedef typename iterator_traits<_InputIterator>::iterator_category _Category;
    __advance(__p, __n, _Category());
}

#endif