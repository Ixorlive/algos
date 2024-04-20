#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t n;
  std::int64_t A;
  std::cin >> n >> A;

  std::vector<std::array<int64_t, 3>> positive_given;
  std::vector<std::array<int64_t, 3>> negative_given;
  positive_given.reserve(n);
  negative_given.reserve(n);
  for (int i = 0; i < n; ++i) {
    int64_t a_i, b_i;
    std::cin >> a_i >> b_i;
    if (b_i >= 0) {
      positive_given.emplace_back(std::array<int64_t, 3>{a_i, b_i, i + 1});
    } else {
      negative_given.emplace_back(std::array<int64_t, 3>{a_i, b_i, i + 1});
    }
  }

  std::sort(positive_given.begin(), positive_given.end(),
            [](const auto &lhs, const auto &rhs) { return lhs[0] < rhs[0]; });
  std::sort(negative_given.begin(), negative_given.end(),
            [](const auto &lhs, const auto &rhs) {
              return lhs[0] + lhs[1] > rhs[0] + rhs[1];
            });
  std::vector<size_t> order_ans;
  order_ans.reserve(n);
  for (const auto &positive_given_person : positive_given) {
    if (positive_given_person[0] > A) {
      break;
    }
    order_ans.emplace_back(positive_given_person[2]);
    A += positive_given_person[1];
  }
  auto comparator = [&](const auto &lhs, const auto &rhs) {
    return lhs[1] > rhs[1];
  };
  std::priority_queue<std::array<int64_t, 3>,
                      std::vector<std::array<int64_t, 3>>, decltype(comparator)>
      p_queue(comparator);
  std::unordered_set<size_t> removed;
  for (const auto &negative_given_person : negative_given) {
    if (negative_given_person[0] <= A) {
      order_ans.emplace_back(negative_given_person[2]);
      A += negative_given_person[1];
      p_queue.push(negative_given_person);
    } else if (!p_queue.empty() &&
               p_queue.top()[1] < negative_given_person[1] &&
               A - p_queue.top()[1] >= negative_given_person[0]) {
      A -= p_queue.top()[1];
      removed.insert(p_queue.top()[2]);
      p_queue.pop();
      order_ans.emplace_back(negative_given_person[2]);
      A += negative_given_person[1];
      p_queue.push(negative_given_person);
    }
  }
  std::cout << order_ans.size() - removed.size() << '\n';
  bool first = true;
  for (const auto &el : order_ans) {
    if (removed.find(el) == removed.end()) {
      std::cout << (first ? "" : " ") << el;
      first = false;
    }
  }
  return 0;
}
