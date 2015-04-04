#ifndef __TUPLE_TYPE_H__
#define __TUPLE_TYPE_H__

#include <tuple>
template <class T, size_t N, class Head, class ...Tail>
struct type_index_impl : type_index_impl<T, N + 1, Tail...>
{
};

template <class T, size_t N, class ...Tail>
struct type_index_impl<T, N, T, Tail...>
{
    const static size_t value = N;
};

template <class T, class ...Args>
T& get_by_type(std::tuple<Args...>& t)
{
    return std::get<type_index_impl<T, 0, Args...>::value>(t);
}

template <class T, class ...Args>
const T& get_by_type(const std::tuple<Args...>& t)
{
    return std::get<type_index_impl<T, 0, Args...>::value>(t);
}
#endif
