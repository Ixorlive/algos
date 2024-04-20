#include <cstdint>
#include <iostream>
#include <vector>

void solve(std::istream &in, std::ostream &out) {
  std::uint64_t n;
  in >> n;
  std::uint64_t d[n + 1];
  d[1] = 1;
  for (std::uint64_t i = 2; i <= n; ++i) {
    std::uint64_t horizonral = i * (i + 1) / 2;
    std::uint64_t j = i - 1;
    std::uint64_t vertical =
        j % 2 == 0 ? (j / 2) * (j / 2 + 1) : ((j + 1) / 2) * ((j + 1) / 2);
    d[i] = d[i - 1] + horizonral + vertical;
  }
  out << d[n];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve(std::cin, std::cout);

  return 0;
}
