#include <iostream>

#include "access/access.h"

struct hidden {
 private:
  int x = 10;
  int func() const &{ return x; }
  int sum(int a, int b) { return a + b; }

  static void sta() {}
};

using tag_hidden_x = access::Tag<class hidden_x>;
template struct access::Accessor<tag_hidden_x, hidden, decltype(hidden::x), &hidden::x>;

using tag_hidden_func = access::Tag<class hidden_func>;
template struct access::Accessor<tag_hidden_func, hidden, decltype(&hidden::func), &hidden::func>;

using tag_hidden_sum = access::Tag<class hidden_sum>;
template struct access::Accessor<tag_hidden_sum, hidden, decltype(&hidden::sum), &hidden::sum>;

using tag_hidden_sta = access::Tag<class hidden_sta>;
template struct access::Accessor<tag_hidden_sta, hidden, decltype(&hidden::sta), &hidden::sta>;

int main() {
  std::cout << std::boolalpha;

  hidden h;
  access::get<tag_hidden_x>(h);

  access::call<tag_hidden_func>(h);
  (h.*access::get<tag_hidden_func>(h))();

  access::call<tag_hidden_sum>(h, 1, 2);
  access::call<tag_hidden_sum>(h, 1, 2);

  access::get<tag_hidden_sta>(h)();
  access::call<tag_hidden_sta>();

  const hidden h2;
  access::get<tag_hidden_x>(h2);

  access::call<tag_hidden_func>(h2);
  (h.*access::get<tag_hidden_func>(h2))();

//  access::call<tag_hidden_sum>(h2, 1, 2);
//  access::call<tag_hidden_sum>(h2, 1, 2);

  access::get<tag_hidden_sta>(h)();
  access::call<tag_hidden_sta>();

  static_assert(std::is_same<access::Type_t<tag_hidden_x>, int>::value, "");



  return 0;
}
