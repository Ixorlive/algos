#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  size_t n_coins, w;
  std::cin >> n_coins >> w;

  std::vector<size_t> coins(n_coins);
  for (int i = 0; i < n_coins; ++i) {
    std::cin >> coins[i];
  }
  std::sort(coins.begin(), coins.end(), std::greater<>());
  std::vector<size_t> ans;
  ans.reserve(n_coins);
  size_t i = 0;
  while (w != 0) {
    if (w >= coins[i]) {
      w -= coins[i];
      ans.emplace_back(coins[i]);
    } else {
      ++i;
    }
  }
  std::cout << ans.size() << std::endl;
  std::copy(ans.begin(), ans.end(), std::ostream_iterator<int>(std::cout, " "));
  return 0;
}
