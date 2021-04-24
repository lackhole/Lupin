//
// Created by YongGyu Lee on 2021-04-24.
//

#ifndef ACCESS_ACCESSOR_H_
#define ACCESS_ACCESSOR_H_

#include "access/tag.h"
#include "access/type_traits.h"

#include <type_traits>

namespace access {

template<typename Tag, typename Class, typename Type, Type ptr_>
struct Accessor {
  using class_type                  = Class;
  using access_type                 = Type;
  using pointer_type                = decltype(ptr_);
  using const_pointer_type          = std::add_const_t<pointer_type>;
  static constexpr pointer_type ptr = ptr_;

  friend auto get_accessor_type_impl(Tag) { return Accessor{}; }
};

}

#endif //ACCESS_ACCESSOR_H_
