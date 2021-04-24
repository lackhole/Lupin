#include <iostream>
#include <string>

#include "access/access.h"

struct hidden {
 private:
  int x = 10;
  std::string str = "hello";
  int func() const &{ return x; }
  int sum(int a, int b) { return a + b; }

  static int sta() { return y; }
  static int y;

};
int hidden::y = 12345;

ACCESS_CREATE_TAG(tag_hidden_x, hidden, x);
ACCESS_CREATE_UNIQUE_TAG(hidden, x);
ACCESS_CREATE_TAG(tag_hidden_str, hidden, str);

ACCESS_CREATE_TAG(tag_hidden_func, hidden, func);
ACCESS_CREATE_TAG(tag_hidden_sum, hidden, sum);
ACCESS_CREATE_TAG(tag_hidden_sta, hidden, sta);
ACCESS_CREATE_TAG(tag_hidden_y, hidden, y);

int main() {
  std::cout << std::boolalpha;

  hidden h;

  std::cout << access::get<tag_hidden_x>(h) << std::endl;
  std::cout << access::get<ACCESS_GET_UNIQUE_TAG(hidden, x)>(h) << std::endl;

  access::get<tag_hidden_x>(h) = 100;
  std::cout << access::get<tag_hidden_x>(h) << std::endl;
  access::get<ACCESS_GET_UNIQUE_TAG(hidden, x)>(h) = 200;
  std::cout << access::get<ACCESS_GET_UNIQUE_TAG(hidden, x)>(h) << std::endl;

  std::cout << access::get<tag_hidden_y>() << std::endl;
  access::get<tag_hidden_y>() = -123;
  std::cout << access::get<tag_hidden_y>() << std::endl;

  access::call<tag_hidden_func>(h);
  (h.*access::get<tag_hidden_func>(h))();

  access::call<tag_hidden_sum>(h, 1, 2);

  access::get<tag_hidden_sta>()();
  access::call<tag_hidden_sta>();

  std::cout << access::get<tag_hidden_str>(h) << std::endl;
  access::get<tag_hidden_str>(std::move(h));
  std::cout << access::get<tag_hidden_str>(h) << std::endl;

  const hidden h2;
  access::get<tag_hidden_x>(h2);

  access::call<tag_hidden_func>(h2);
  (h.*access::get<tag_hidden_func>(h2))();

  std::cout << access::get<tag_hidden_sta>()() << std::endl;
  std::cout << access::call<tag_hidden_sta>() << std::endl;

  static_assert(std::is_same<access::Type_t<tag_hidden_x>, int>::value, "");
  static_assert(std::is_same<access::Type_t<tag_hidden_y>, int>::value, "");

  // Note that the below two type is different. Choose your own way.
  static_assert(std::is_same<access::Type_t<tag_hidden_func>, int () const&>::value, "");                                           // function type
  static_assert(std::is_same<decltype(access::get<tag_hidden_func>(std::declval<hidden>())), int (hidden::*)() const&>::value, ""); // function pointer type

  // Note that these three are different too
  static_assert(std::is_same<access::Type_t<tag_hidden_sta>, int()>::value, "");
  static_assert(std::is_same<decltype(access::get<tag_hidden_sta>()), int(&)()>::value, "");
  static_assert(std::is_same<std::decay_t<decltype(access::get<tag_hidden_sta>())>, int(*)()>::value, "");

  return 0;
}
