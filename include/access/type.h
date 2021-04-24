//
// Created by YongGyu Lee on 2021-04-24.
//

#ifndef ACCESS_TYPE_H
#define ACCESS_TYPE_H

#include "access/tag.h"

namespace access {

template<typename Tag>
struct Type {
  using type = typename TagTraits<Tag>::access_type;
};

template<typename Tag>
using Type_t = typename Type<Tag>::type;

}

#endif //ACCESS_TYPE_H
