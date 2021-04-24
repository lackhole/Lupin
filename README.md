# Access
#### A generic library for accessing class members, ignoring their access specifiers.  

* No need to modify the target class
* No need to overwrite access specifiers with macros
* Not using dirty pointer-offset, making it more flexible on changes.


* Header-only
* Compile-time traits, zero runtime overhead.
* Only requires the name of the class and member
* Can be useful when testing private/protected members or functions.

## Requirements
### C++ Version
* C++14 or higher
### Compiler Support

| Compiler | Minimum version |
|----------|-----------------|
| gcc      |       6.0       |
| clang    |       8.0       |
| MSVC     |19.14(below not tested)|

## Limitations
* Does not work on template type members.
* Does not work on overloaded functions.

## Examples
Whole example can be found [here](main.cpp)

### Motivating Example 1
```
#include <iostream>

#include "access/access.hpp"

struct foo {
 private:
  std::string name = "hello";
  int age = 27;
  void print() {}
};

// Tag will be used when accessing private/protected/public data.
// One tag coresponds to one member of a class.
// After the tag is named, it has to be enabled using access::Accessor

using tag_foo_name = access::Tag<class foo_name>;
template struct access::Accessor<tag_foo_name, foo, decltype(&foo::name), &foo::name>;

int main() {
  foo f;
  
  // peek hidden data
  std::cout << access::get<tag_foo_name>(f) << '\n'; // "hello"
  
  // steal hidden data
  access::get<tag_foo_name>(f) = "lupin";
  std::cout << access::get<tag_foo_name>(f) << '\n'; // "lupin"
}
```

### Motivating Example 2
```
#include <iostream>

#include "access/access.hpp"

struct foo {
 private:
  std::string name = "hello";
  int age = 27;
  void print() {}
};

// simplified using macro
ACCESS_CREATE_TAG(my_tag_123, hidden, x);
ACCESS_CREATE_UNIQUE_TAG(hidden, x);

int main() {
  foo f;
  
  auto a = access::get<my_tag_123>(h);                        // named tag access
  auto b = access::get<ACCESS_GET_UNIQUE_TAG(hidden, x)>(h);  // unnamed tag(unique) access
}
```

### Motivating Example 3
```
#include "access/access.hpp"

struct foo {
 private:
  std::string name = "hello";
  int age = 27;
  void print() {}
};

ACCESS_CREATE_TAG(tag_foo_print, foo, print);

int main() {
  foo f;
  
  // call hidden function
  access::call<tag_foo_print>(f);           // call directly
  (f.*access::get<tag_foo_print>(f))();     // call manually after getting its pointer
}
```

### Motivating Example 4
```
#include "access/access.hpp"

struct foo {
 private:
  std::string name = "hello";
  int age = 27;
  void print() {}
};

ACCESS_CREATE_TAG(tag_foo_age, foo, print);

int main() {
  foo f;
  
  // get type of hidden data
  static_assert(std::is_same<access::Type_t<tag_foo_age>, int>::value, "");
}
```
