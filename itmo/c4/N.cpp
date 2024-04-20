#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

typedef uint64_t ui64;
typedef int64_t i64;

void Stars(std::istream &in, std::ostream &out) {
  ui64 n;
  while (in >> n) {
    constexpr i64 MAX_X = 32010;
    vector<i64> v(MAX_X, 0);
    vector<i64> lvl(n, 0);
    for (ui64 i = 0; i < n; ++i) {
      i64 x, y;
      in >> x >> y;
      ++x;
      i64 s = 0;
      i64 k = x;
      while (k > 0) {
        s += v[k];
        k -= (k & (-k));
      }
      ++lvl[s];
      i64 start = 1;
      while (x <= MAX_X) {
        v[x] += start;
        x += (x & (-x));
      }
    }
    std::copy(lvl.begin(), lvl.end(), std::ostream_iterator<i64>(out, "\n"));
  }
}

void Test(){{std::istringstream in{"5\n"
                                   "1 1\n"
                                   "5 1\n"
                                   "7 1\n"
                                   "3 3\n"
                                   "5 5\n"
                                   "1\n"
                                   "13 230"};
std::ostringstream out;
Stars(in, out);
cout << out.str();
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  Stars(std::cin, std::cout);
  return 0;
}
