#include <iostream>
#include <numeric>
#include <vector>

void Ropes(std::istream &in, std::ostream &out) {
  size_t N, K;
  in >> N >> K;
  size_t sum = 0;
  size_t max = 0;
  std::vector<size_t> ropes(N);
  for (size_t i = 0; i < N; ++i) {
    in >> ropes[i];
    if (ropes[i] > max) {
      max = ropes[i];
    }
  }
  // auto min_rope = std::max(sum / K, min);
  auto min_rope = max;
  size_t l = 1;
  size_t ans = 0;
  while (l <= min_rope) {
    auto mid = l + (min_rope - l) / 2;
    auto val =
        std::accumulate(ropes.begin(), ropes.end(), 0,
                        [mid](int acc, size_t val) { return acc + val / mid; });
    if (val >= K) {
      ans = mid;
      l = mid + 1;
    } else {
      min_rope = mid - 1;
    }
  }
  out << ans;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  Ropes(std::cin, std::cout);
}
