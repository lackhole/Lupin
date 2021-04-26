//
// Created by YongGyu Lee on 2021-04-24.
//

#ifndef ACCESS_MACRO_H_
#define ACCESS_MACRO_H_

#define ACCESS_CONCAT_IMPL(x, y) x##_##y
#define ACCESS_CONCAT(x, y) ACCESS_CONCAT_IMPL(x,y)

#define ACCESS_ENABLE_TAG(tag, clazz, member)                                               \
  template struct ::access::Accessor<tag, clazz, decltype(&clazz::member), &clazz::member>

// class_name, member_name
#define ACCESS_CREATE_UNIQUE_TAG(clazz, member) \
  ACCESS_ENABLE_TAG(::access::Tag<class ACCESS_CONCAT(clazz, member)>, clazz, member)

// tag_name, class_name, member_name
#define ACCESS_CREATE_TAG(tag, clazz, member)                               \
  using tag = ::access::Tag<class ACCESS_CONCAT(ACCESS_CONCAT(ACCESS_CONCAT(access_dummy$1znq_baf,clazz), member), __LINE__)>;  \
  ACCESS_ENABLE_TAG(tag, clazz, member)

// class_name, member_name, template_parameters...(if necessary)
#define ACCESS_GET_UNIQUE_TAG(clazz, member)          \
  ::access::Tag<ACCESS_CONCAT(clazz, member)>


#endif //ACCESS_MACRO_H_
