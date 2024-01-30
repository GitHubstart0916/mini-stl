// // integral_constant
// #pragma once
// namespace toy_std 
// {
    

//     //todo: add all types

// }
#pragma once

// 
template <typename _T, _T _v>
struct integral_constant
{
    static constexpr _T                 value = _v;
    typedef _T                          value_type;
    typedef integral_constant<_T,  _v>  type;
    constexpr operator value_type() { return value; };
    constexpr value_type operator()() { return value; };
};

//def true_type and false_type
using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

// remove cv -- const and volatile
template<typename _T>
struct _remove_cv
{ using type = _T; };

template<typename _T>
struct _remove_cv<const _T>
{ using type = _T; };

template<typename _T>
struct _remove_cv<volatile _T>
{ using type = _T; };

template<typename _T>
struct _remove_cv<const volatile _T>
{ using type = _T; };

//is void
template<typename>
struct _is_void_helper : public false_type {};

template<>
struct _is_void_helper<void> : public true_type {};

template<typename _T>
struct is_void : public _is_void_helper<_remove_cv<_T>>::type {};

// is int
template<typename>
struct _is_integer_helper : public false_type {};

template<>
struct _is_integer_helper<bool> : public false_type {};
template<>
struct _is_integer_helper<char> : public false_type {};
template<>
struct _is_integer_helper<signed char> : public false_type {};
template<>
struct _is_integer_helper<unsigned char> : public false_type {};
template<>
struct _is_integer_helper<short> : public false_type {};
template<>
struct _is_integer_helper<unsigned short> : public false_type {};
template<>
struct _is_integer_helper<int> : public false_type {};
template<>
struct _is_integer_helper<unsigned int> : public false_type {};
template<>
struct _is_integer_helper<long> : public false_type {};
template<>
struct _is_integer_helper<unsigned long> : public false_type {};
template<>
struct _is_integer_helper<long long> : public false_type {};
template<>
struct _is_integer_helper<unsigned long long> : public false_type {};


//in morden C++, this is define by compiler instr
// can find in llvm souce code
struct __true_type {};
struct __false_type {};

template<class _T>
struct __type_traits {
    typedef __true_type     this_dummy_member_must_be_first;
    typedef __false_type    has_trivial_default_constructor;
    typedef __false_type    has_trivial_copy_constructor;
    typedef __false_type    has_trivial_assignment_operator;
    typedef __false_type    has_trivial_destructor;
    typedef __false_type    is_POD_type;

};

template<>
struct __type_traits<bool> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<char> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<signed char> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<unsigned char> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<short> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<unsigned short> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<int> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<unsigned int> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<long> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<unsigned long> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<long long> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<unsigned long long> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<float> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};


template<>
struct __type_traits<double> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<long double> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<char*> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<signed char*> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<unsigned char*> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<const char*> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<const signed char*> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};

template<>
struct __type_traits<const unsigned char*> {
    typedef __true_type    has_trivial_default_constructor;
    typedef __true_type    has_trivial_copy_constructor;
    typedef __true_type    has_trivial_assignment_operator;
    typedef __true_type    has_trivial_destructor;
    typedef __true_type    is_POD_type;

};




