# Access
#### A generic programming for accessing class members, ignoring their access specifiers.  

* No need to modify target class
* No need to macro-ing specifiers
* Not using dirty pointer-offset, making it more flexible on class change. 

## Requirements
### C++ Version
* C++11 or higher
### Compiler Support

| Compiler | Minimum version |
|----------|-----------------|
| gcc      |       6.0       |
| clang    |       8.0       |
| MSVC     |19.14(below not tested)|

## Examples
```
#include "access/access.hpp"

struct foo {
 private:
  std::string name = "hello";
  int age = 27;
  void print() {}
};

using tag_foo_name = access::Tag<class foo_name>;
template struct access::Accessor<tag_foo_name, foo, decltype(&foo::name), &foo::name>;

using tag_foo_print = access::Tag<class foo_print>;
template struct access::Accessor<tag_foo_print, foo, decltype(&foo::print), &foo::print>;

int main() {
  foo f;
  std::cout << access::get<tag_foo_name>(f) << '\n'; // "hello"
  
  access::get<tag_foo_name>(f) = "lupin";
  std::cout << access::get<tag_foo_name>(f) << '\n'; // "lupin"
  
  access::call<tag_foo_print>(f); // call directly
  (f.*access::get<tag_foo_print>(f))(); // call after getting pointer
}
```

