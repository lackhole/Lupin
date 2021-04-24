//
// Created by YongGyu Lee on 2021-04-24.
//

#ifndef ACCESS_TYPE_H
#define ACCESS_TYPE_H

#include "access/tag.h"
#include "access/type_traits.h"

namespace access {

template<typename Tag>
struct Type {
  using type = get_pointing_type_t<typename TagTraits<Tag>::access_type>;
};

template<typename Tag>
using Type_t = typename Type<Tag>::type;

}

#endif //ACCESS_TYPE_H
