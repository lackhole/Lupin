//
// Created by YongGyu Lee on 2021-04-24.
//

#ifndef ACCESS_TAG_H_
#define ACCESS_TAG_H_

namespace access {

template<typename Dummy>
struct Tag {
  friend auto get_accessor_type_impl(Tag);
};

template<typename Tag>
struct TagTraits {
  using tag_type = Tag;
  using accessor_type       = decltype(get_accessor_type_impl(std::declval<tag_type>()));
  using class_type          = typename accessor_type::class_type;
  using access_type         = typename accessor_type::access_type;
  using pointer_type        = typename accessor_type::pointer_type;
};

}

#endif //ACCESS_TAG_H_
