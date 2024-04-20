#include <cstdint>
#include <iostream>
#include <sstream>

using namespace std;

using ull = std::uint64_t;

ull thue_morse_prefix_sum(ull x) {
  if (x % 2 == 0) {
    return x / 2 + (__builtin_popcountll(x) % 2);
  }
  return (x + 1) / 2;
}

void Antihash(std::istream &in, std::ostream &out) {
  int n;
  in >> n;
  for (int i = 0; i < n; ++i) {
    ull li, ri;
    in >> li >> ri;
    out << thue_morse_prefix_sum(ri) -
               (li > 0 ? thue_morse_prefix_sum(li - 1) : 0)
        << '\n';
  }
}

void Test(){{std::istringstream in{"2\n"
                                   "1 4\n"
                                   "2047 2048"};
std::ostringstream out;
Antihash(in, out);
cout << out.str();
//    assert(out.str() == "4");
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //  for (int i = 0; i < 20; ++i) {
  //    std::cout << "i = " << i << ": " << thue_morse_prefix_sum(i) << '\n';
  //  }
  //  Test();
  Antihash(std::cin, std::cout);
  return 0;
}
