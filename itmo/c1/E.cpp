#include <algorithm>
#include <cstdint>
#include <deque>
#include <iostream>
#include <iterator>

static const std::uint32_t EXP = 1 << 30;

void print(const std::deque<std::uint64_t> &values, std::ostream &out) {
  std::copy(values.begin(), values.end(),
            std::ostream_iterator<std::uint64_t>(out, " "));
  out << "\n\n";
}

void BoardBeforeProfSlept(std::istream &in, std::ostream &out) {
  size_t n, k;
  in >> n >> k;
  std::deque<std::uint64_t> values;
  // values.reserve(n);
  for (size_t i = 0; i < n; ++i) {
    std::uint64_t val;
    in >> val;
    values.push_back(val);
  }
  if (values.empty())
    return;
  if (values.size() == 1) {
    out << 0;
    return;
  }
  for (size_t i = 0; i < k; ++i) {
    auto first = values.front();
    auto last = values.back();
    if (first < last) {
      values.pop_front();
      values.push_back((first + last) & ((1 << 30) - 1));
    } else {
      values.pop_back();
      values.push_front(first == last ? 0 : EXP - (first - last));
    }
  }
  auto last = values.back();
  values.pop_back();
  std::copy(values.begin(), values.end(),
            std::ostream_iterator<std::uint64_t>(out, " "));
  out << last;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  BoardBeforeProfSlept(std::cin, std::cout);
}
