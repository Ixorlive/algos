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
  vi P(n);
  for (int i = 0; i < n; ++i) {
    in >> P[i];
  }
  vi Z(n);
  for (int i = 1; i < n; ++i) {
    if (P[i]) {
      Z[i - P[i] + 1] = P[i];
    }
  }
  Z[0] = n;
  if (Z[1]) {
    for (int i = 1; i < Z[1]; ++i) {
      Z[i + 1] = Z[1] - i;
    }
  }
  int k;
  for (int i = Z[1] + 1; i < n - 1; ++i) {
    k = i;
    if (Z[i] && !Z[i + 1]) {
      for (int j = 1; j < Z[i] && Z[i + j] <= Z[j]; ++j) {
        Z[i + j] = min(Z[j], Z[i] - j);
        k = i + j;
      }
    }
    i = k;
  }
  std::copy(Z.begin(), Z.end(), ostream_iterator<int>(out, " "));
}

void Test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  solve(std::cin, std::cout);
}

void Test(){{std::istringstream in("8\n"
                                   "0 0 1 0 1 2 3 1");
std::ostringstream out;
solve(in, out);
std::cout << out.str();
//    assert(out.str() == "20 40 20 0 -1");
}
}
;
