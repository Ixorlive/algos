#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

void FastSearch(std::istream &in, std::ostream &out) {
  size_t n;
  in >> n;
  std::vector<std::int32_t> src(n);
  for (size_t i = 0; i < n; ++i) {
    in >> src[i];
  }
  std::sort(src.begin(), src.end());
  size_t k;
  in >> k;
  bool first = true;
  for (size_t i = 0; i < k; ++i) {
    std::int32_t L, R;
    in >> L >> R;
    auto l_bound = std::lower_bound(src.begin(), src.end(), L);
    auto r_bound = std::upper_bound(src.begin(), src.end(), R);
    out << (first ? "" : " ") << r_bound - l_bound;
    first = false;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  FastSearch(std::cin, std::cout);
}
