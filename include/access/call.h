//
// Created by YongGyu Lee on 2021-04-24.
//

#ifndef ACCESS_CALL_H_
#define ACCESS_CALL_H_

#include "access/tag.h"

#include <type_traits>
#include <utility>

namespace access {

/** call non-static member function */

template<typename Tag, typename Target, typename ...Args>
inline constexpr decltype(auto)
call(Target&& target, Args&&... args) {
  using tag_traits    = TagTraits<Tag>;
  using access_type   = typename tag_traits::access_type;
  using accessor_type = typename tag_traits::accessor_type;
  using pointer_type  = typename tag_traits::pointer_type;

  static_assert(!std::is_function<std::remove_pointer_t<pointer_type>>::value, "Static function doest not require a instance");
  static_assert(std::is_member_function_pointer<access_type>::value, "Tag must represent non-static member function");
  return (std::forward<Target>(target).*accessor_type::ptr)(std::forward<Args>(args)...);
}

/** call static member function */

template<typename Tag, typename ...Args>
inline constexpr decltype(auto)
call(Args&&... args) {
  using tag_traits = TagTraits<Tag>;
  using access_type = typename tag_traits::access_type;
  using accessor_type = typename tag_traits::accessor_type;

  static_assert(!std::is_member_function_pointer<access_type>::value &&
                std::is_function<std::remove_pointer_t<access_type>>::value,
                "Tag must represent a static member function");
  return (accessor_type::ptr)(std::forward<Args>(args)...);
}

}

#endif //ACCESS_CALL_H_
