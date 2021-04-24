//
// Created by YongGyu Lee on 2021-04-24.
//

#ifndef ACCESS_IS_FUNCTION_H
#define ACCESS_IS_FUNCTION_H

#include <type_traits>

namespace access {
template<typename T>
struct is_function : std::conditional_t<
    std::is_member_function_pointer<std::decay_t<T>>::value || std::is_function<std::remove_pointer_t<T>>::value,
  std::true_type, std::false_type> {};

}

#endif //ACCESS_IS_FUNCTION_H
