//
// Created by cosge on 2021-04-24.
//

#ifndef ACCESS_MACRO_H
#define ACCESS_MACRO_H

#define ACCESS_CONCAT2(x, y) x ## y
#define ACCESS_CONCAT(x, y) ACCESS_CONCAT2(x, y)

#define ACCESS_CREATE_TAG_IMPL(class_name, member_name)           \
    ::access::Tag<class ACCESS_CONCAT(class_name, ACCESS_CONCAT(_, ACCESS_CONCAT(member_name, ACCESS_CONCAT(_, __LINE__))))>;

#define ACCESS_CREATE_TAG_1(c,_1) ACCESS_CREATE_TAG_IMPL(c,_1) // default
#define ACCESS_CREATE_TAG_2(c,_1,_2) ACCESS_CREATE_TAG_IMPL(c,_1##_2)
#define ACCESS_CREATE_TAG_3(c,_1,_2,_3) ACCESS_CREATE_TAG_IMPL(c,_1##_2##_3)
#define ACCESS_CREATE_TAG_4(c,_1,_2,_3,_4) ACCESS_CREATE_TAG_IMPL(c, _1##_2##_3##_4)
#define ACCESS_CREATE_TAG_5(c,_1,_2,_3,_4,_5) ACCESS_CREATE_TAG_IMPL(c, _1##_2##_3##_4##_5)
#define ACCESS_CREATE_TAG_6(c,_1,_2,_3,_4,_5,_6) ACCESS_CREATE_TAG_IMPL(c, _1##_2##_3##_4##_5##_6)
#define ACCESS_CREATE_TAG_7(c,_1,_2,_3,_4,_5,_6,_7) ACCESS_CREATE_TAG_IMPL(c, _1##_2##_3##_4##_5##_6##_7)
#define ACCESS_CREATE_TAG_8(c,_1,_2,_3,_4,_5,_6,_7,_8) ACCESS_CREATE_TAG_IMPL(c, _1##_2##_3##_4##_5##_6##_7##_8)
#define ACCESS_CREATE_TAG_9(c,_1,_2,_3,_4,_5,_6,_7,_8,_9) ACCESS_CREATE_TAG_IMPL(c, _1##_2##_3##_4##_5##_6##_7##_8##_9)
#define ACCESS_CREATE_TAG_10(c,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10) ACCESS_CREATE_TAG_IMPL(c, _1##_2##_3##_4##_5##_6##_7##_8##_9##_10)


#define ACCESS_CREATE_TAG_N(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,N,...) ACCESS_CREATE_TAG_##N

#define ACCESS_CREATE_TAG(...) ACCESS_CREATE_TAG_N(__VA_ARGS__,10,9,8,7,6,5,4,3,2,1) (__VA_ARGS__)


#define ACCESS_CREATE_ACCESSOR(tag, class_name, member_name) \
  template struct ::access::Accessor<tag, class_name, decltype(&class_name::member_name), &class_name::member_name>;


#endif //ACCESS_MACRO_H
