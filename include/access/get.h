//
// Created by YongGyu Lee on 2021-04-24.
//

#ifndef ACCESS_GET_H_
#define ACCESS_GET_H_

#include "access/tag.h"

#include <type_traits>
#include <utility>

namespace access {

/** get non-static member variable */

template<typename Tag, typename Target>
inline constexpr
std::enable_if_t<!is_function<typename TagTraits<Tag>::access_type>::value,
    get_pointing_type_t<typename TagTraits<Tag>::access_type> &>
get(Target& target) {
  return target.*TagTraits<Tag>::accessor_type::ptr;
}

template<typename Tag, typename Target>
inline constexpr
std::enable_if_t<!is_function<typename TagTraits<Tag>::access_type>::value,
    get_pointing_type_t<typename TagTraits<Tag>::access_type> const &>
get(const Target& target) {
  return target.*TagTraits<Tag>::accessor_type::ptr;
}

template<typename Tag, typename Target>
inline constexpr
std::enable_if_t<!is_function<typename TagTraits<Tag>::access_type>::value,
    get_pointing_type_t<typename TagTraits<Tag>::access_type>>
get(Target&& target) {
  return std::forward<Target>(target).*TagTraits<Tag>::accessor_type::ptr;
}

template<typename Tag, typename Target>
inline constexpr
std::enable_if_t<!is_function<typename TagTraits<Tag>::access_type>::value,
    get_pointing_type_t<typename TagTraits<Tag>::access_type>>
get(const Target&& target) {
  return std::forward<Target>(target).*TagTraits<Tag>::accessor_type::ptr;
}

/** get non-static member function pointer */

template<typename Tag, typename Target>
inline constexpr
std::enable_if_t<is_function<typename TagTraits<Tag>::access_type>::value,
    typename TagTraits<Tag>::access_type>
get(Target& target) {
  return TagTraits<Tag>::accessor_type::ptr;
}

template<typename Tag, typename Target>
inline constexpr
std::enable_if_t<is_function<typename TagTraits<Tag>::access_type>::value,
    typename TagTraits<Tag>::access_type const>
get(const Target& target) {
  return TagTraits<Tag>::accessor_type::ptr;
}

template<typename Tag, typename Target>
inline constexpr
std::enable_if_t<is_function<typename TagTraits<Tag>::access_type>::value,
    typename TagTraits<Tag>::access_type>
get(Target&& target) {
  return TagTraits<Tag>::accessor_type::ptr;
}

template<typename Tag, typename Target>
inline constexpr
std::enable_if_t<is_function<typename TagTraits<Tag>::access_type>::value,
    typename TagTraits<Tag>::access_type const>
get(const Target&& target) {
  return TagTraits<Tag>::accessor_type::ptr;
}

/** get static member (both variable and function) */

template<typename Tag>
std::enable_if_t<!is_function<typename TagTraits<Tag>::access_type>::value,
    get_pointing_type_t<typename TagTraits<Tag>::access_type> &>
get() {
  return *TagTraits<Tag>::accessor_type::ptr;
}

template<typename Tag>
std::enable_if_t<is_function<typename TagTraits<Tag>::access_type>::value,
    typename TagTraits<Tag>::access_type>
get() {
  return *TagTraits<Tag>::accessor_type::ptr;
}


}

#endif //ACCESS_GET_H_
