//
// Created by YongGyu Lee on 2021-04-24.
//

#ifndef ACCESS_GET_H_
#define ACCESS_GET_H_

#include "access/tag.h"

#include <type_traits>

namespace access {

template<typename Tag, typename Target>
inline constexpr
std::enable_if_t<!is_function<typename TagTraits<Tag>::access_type>::value, typename TagTraits<Tag>::access_type &>
get(Target& target) {
  return target.*TagTraits<Tag>::accessor_type::ptr;
}

template<typename Tag, typename Target>
inline constexpr
std::enable_if_t<!is_function<typename TagTraits<Tag>::access_type>::value, typename TagTraits<Tag>::access_type const&>
get(const Target& target) {
  return target.*TagTraits<Tag>::accessor_type::ptr;
}


template<typename Tag, typename Target>
inline constexpr
std::enable_if_t<is_function<typename TagTraits<Tag>::access_type>::value, typename TagTraits<Tag>::access_type>
get(Target& target) {
  return TagTraits<Tag>::accessor_type::ptr;
}

template<typename Tag, typename Target>
inline constexpr
std::enable_if_t<is_function<typename TagTraits<Tag>::access_type>::value, typename TagTraits<Tag>::access_type const>
get(const Target& target) {
  return TagTraits<Tag>::accessor_type::ptr;
}


}

#endif //ACCESS_GET_H_
