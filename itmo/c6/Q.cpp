#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

typedef uint64_t ui64;
typedef int64_t i64;
typedef uint32_t ui32;
typedef int32_t i32;
typedef uint16_t ui16;
typedef int16_t i16;
typedef uint8_t ui8;
typedef int8_t i8;
using namespace std;

using vi = vector<int>;

void solve(std::istream &in, std::ostream &out) {
  int n;
  in >> n;
  vi Z(n);
  for (int i = 0; i < n; ++i) {
    in >> Z[i];
  }
  vi P(n);
  for (int i = 1; i < n; ++i) {
    if (Z[i]) {
      for (int j = Z[i] - 1; j >= 0 && !(P[i + j]); --j) {
        P[i + j] = j + 1;
      }
    }
  }
  std::copy(P.begin(), P.end(), ostream_iterator<int>(out, " "));
}

void Test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  solve(std::cin, std::cout);
}

void Test(){{std::istringstream in(
    "20\n"
    "20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1");
std::ostringstream out;
solve(in, out);
std::cout << out.str();
//    assert(out.str() == "20 40 20 0 -1");
}
}
;
