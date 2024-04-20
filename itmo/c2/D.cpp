#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t n;
  std::cin >> n;
  std::vector<std::array<size_t, 3>> a(n); // a_i, b_i, id
  for (int j = 0; j < n; ++j) {
    std::cin >> a[j][0];
    a[j][2] = j + 1;
  }
  for (int j = 0; j < n; ++j) {
    std::cin >> a[j][1];
  }

  std::sort(a.begin(), a.end(), [](const auto &lhs, const auto &rhs) {
    return (lhs[0] + lhs[1]) > (rhs[0] + rhs[1]);
  });

  std::vector<size_t> order(n);

  for (int i = 0; i < n - 1; ++i) {
    order[i] = a[i][2];
    if (a[i][1] <= a[i + 1][0]) {
      std::cout << -1;
      return 0;
    }
  }
  order[n - 1] = a.back()[2];
  std::copy(order.begin(), order.end(),
            std::ostream_iterator<int>(std::cout, " "));

  return 0;
}
