//
// Created by YongGyu Lee on 2021-04-24.
//

#ifndef ACCESS_CALL_H_
#define ACCESS_CALL_H_

#include "access/tag.h"

#include <type_traits>

namespace access {

/** call non-static member function */

template<typename Tag, typename Target, typename ...Args>
inline constexpr auto
call(Target&& target, Args&&... args)
  -> decltype((std::forward<Target>(target).*TagTraits<Tag>::accessor_type::ptr)(std::forward<Args>(args)...))
{
  using tag_traits = TagTraits<Tag>;
  using access_type = typename tag_traits::access_type;
  using accessor_type = typename tag_traits::accessor_type;

  static_assert(std::is_member_function_pointer<access_type>::value,
                "Tag must represent member function, or perhaps the tag represents static member function");
  return (std::forward<Target>(target).*accessor_type::ptr)(std::forward<Args>(args)...);
}

/** gcc < 10 cannot compile the below overloads */

//template<typename Tag, typename Target, typename ...Args>
//inline constexpr decltype(auto)
//call(Target& target, Args&&... args) {
//  using tag_traits = TagTraits<Tag>;
//  using access_type = typename tag_traits::access_type;
//  using accessor_type = typename tag_traits::accessor_type;
//
//  static_assert(std::is_member_function_pointer<access_type>::value,
//                "Tag must represent member function, or perhaps the tag represents static member function");
//  return (target.*accessor_type::ptr)(std::forward<Args>(args)...);
//}
//
//template<typename Tag, typename Target, typename ...Args>
//inline constexpr decltype(auto)
//call(const Target& target, Args&&... args) {
//  using tag_traits = TagTraits<Tag>;
//  using access_type = typename tag_traits::access_type;
//  using accessor_type = typename tag_traits::accessor_type;
//
//  static_assert(std::is_member_function_pointer<access_type>::value,
//                "Tag must represent member function, or perhaps the tag represents static member function");
//  return (target.*accessor_type::ptr)(std::forward<Args>(args)...);
//}
//
//template<typename Tag, typename Target, typename ...Args>
//inline constexpr decltype(auto)
//call(const Target&& target, Args&&... args) {
//  using tag_traits = TagTraits<Tag>;
//  using access_type = typename tag_traits::access_type;
//  using accessor_type = typename tag_traits::accessor_type;
//
//  static_assert(std::is_member_function_pointer<access_type>::value,
//                "Tag must represent member function, or perhaps the tag represents static member function");
//  return (std::forward<Target>(target).*accessor_type::ptr)(std::forward<Args>(args)...);
//}

/** call static member function */

template<typename Tag, typename ...Args>
inline constexpr auto
call(Args&&... args)
  -> decltype((TagTraits<Tag>::accessor_type::ptr)(std::forward<Args>(args)...))
{
  using tag_traits = TagTraits<Tag>;
  using access_type = typename tag_traits::access_type;
  using accessor_type = typename tag_traits::accessor_type;

  static_assert(!std::is_member_function_pointer<access_type>::value && std::is_function<std::remove_pointer_t<access_type>>::value,
                "Tag must represent static member function");
  return (accessor_type::ptr)(std::forward<Args>(args)...);
}

}

#endif //ACCESS_CALL_H_
