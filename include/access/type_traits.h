//
// Created by YongGyu Lee on 2021-04-24.
//

#ifndef ACCESS_TYPE_TRAITS_H
#define ACCESS_TYPE_TRAITS_H

#include <type_traits>

namespace access {

template<typename T>
struct is_function : std::conditional<
    std::is_member_function_pointer<std::decay_t<T>>::value ||
    std::is_function<typename std::remove_pointer<T>::type>::value,
  std::true_type, std::false_type>::type {};

template<typename T>
struct get_pointing_type {
  using type = T;
};

template<typename T>
struct get_pointing_type<T*> {
  using type = T;
};

template<typename T, typename Class>
struct get_pointing_type<T Class::*> {
  using type = T;
};

template<typename T>
using get_pointing_type_t = typename get_pointing_type<T>::type;

}

#endif //ACCESS_TYPE_TRAITS_H
