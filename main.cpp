#include <iostream>
#include <string>

#include "access/access.h"

struct hidden {
 private:
  int x = 10;
  std::string str = "hello";
  int func() const &{ return x; }
  int sum(int a, int b) { return a + b; }

  void rrefOnly() && {}

  static int sta() { return y; }
  static int y;

  virtual int vf() { return 1; }
};
int hidden::y = 12345;

struct base {
 private:
  virtual void vf() { std::cout << "base\n"; }
};

struct derived : public base {
 private:
  void vf() override { std::cout << "derived\n"; }
};

ACCESS_CREATE_TAG(tag_hidden_x, hidden, x);
ACCESS_CREATE_UNIQUE_TAG(hidden, x);
ACCESS_CREATE_TAG(tag_hidden_str, hidden, str);

ACCESS_CREATE_TAG(tag_hidden_func, hidden, func);
ACCESS_CREATE_TAG(tag_hidden_sum, hidden, sum);
ACCESS_CREATE_TAG(tag_hidden_sta, hidden, sta);
ACCESS_CREATE_TAG(tag_hidden_y, hidden, y);
ACCESS_CREATE_TAG(tag_hidden_rref, hidden, rrefOnly);

ACCESS_CREATE_UNIQUE_TAG(base, vf);

int main() {

  hidden h;

  // can read and write private member
  std::cout << access::get<tag_hidden_x>(h) << std::endl;
  access::get<tag_hidden_x>(h) = 100;
  std::cout << access::get<tag_hidden_x>(h) << std::endl;

  std::cout << access::get<tag_hidden_str>(h) << std::endl;
  access::get<tag_hidden_str>(std::move(h));
  std::cout << access::get<tag_hidden_str>(h) << std::endl;

  // using unnamed(unique) tag
  std::cout << access::get<ACCESS_GET_UNIQUE_TAG(hidden, x)>(h) << std::endl;
  access::get<ACCESS_GET_UNIQUE_TAG(hidden, x)>(h) = 200;
  std::cout << access::get<ACCESS_GET_UNIQUE_TAG(hidden, x)>(h) << std::endl;

  // can read and write static private member
  std::cout << access::get<tag_hidden_y>() << std::endl;
  access::get<tag_hidden_y>() = -123;
  std::cout << access::get<tag_hidden_y>() << std::endl;

  // can call private member function
  access::call<tag_hidden_func>(h);
  (h.*access::get<tag_hidden_func>(h))();

  // value types overloads
  access::call<tag_hidden_sum>(h, 1, 2);
  access::call<tag_hidden_sum>(std::move(h), 1, 2);
//  access::call<tag_hidden_rref>(h);
  access::call<tag_hidden_rref>(hidden());

  // can call private static member function
  access::call<tag_hidden_sta>();
  access::get<tag_hidden_sta>()();
//  access::call<tag_hidden_sta>(h);


  const hidden h2;

  // const overload is read-only
  access::get<tag_hidden_x>(h2);
//  access::get<tag_hidden_x>(h2) = 132;

  access::call<tag_hidden_func>(h2);
  (h2.*access::get<tag_hidden_func>(h2))();

  // Note that access::Type_t returns actual type, while access::get returns it's reference
  static_assert(std::is_same<access::Type_t<tag_hidden_x>, int>::value, "");
  static_assert(std::is_same<decltype(access::get<tag_hidden_x>(h)), int&>::value, "");

  // Same applies to the static member variables
  static_assert(std::is_same<access::Type_t<tag_hidden_y>, int>::value, "");
  static_assert(std::is_same<decltype(access::get<tag_hidden_y>()), int&>::value, "");

  // Note that type of function is different too
  static_assert(std::is_same<access::Type_t<tag_hidden_func>, int() const&>::value, "");                                            // function type
  static_assert(std::is_same<decltype(access::get<tag_hidden_func>(std::declval<hidden>())), int (hidden::*)() const&>::value, ""); // function pointer type

  // Same applies to the static member function
  static_assert(std::is_same<access::Type_t<tag_hidden_sta>, int()>::value, "");              // function type
  static_assert(std::is_same<decltype(access::get<tag_hidden_sta>()), int(*)()>::value, "");  // function pointer type


  // private virtual function can be called
  base b;
  derived d;

  access::call<ACCESS_GET_UNIQUE_TAG(base, vf)>(b);
  access::call<ACCESS_GET_UNIQUE_TAG(base, vf)>(d);
  access::call<ACCESS_GET_UNIQUE_TAG(base, vf)>(static_cast<base &>(d));

  return 0;
}
