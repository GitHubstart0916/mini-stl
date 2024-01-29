// integral_constant
#pragma once
namespace toy_std 
{
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

    //todo: add all types

}
