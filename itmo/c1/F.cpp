#include <cstdint>
#include <deque>
#include <iostream>
#include <queue>

template <typename T> class MinQueue {
public:
  void clear() {
    while (!queue_.empty())
      queue_.pop();
    while (!mins_.empty())
      mins_.pop_back();
  }

  void push(T element) {
    if (queue_.empty()) {
      queue_.push(element);
      mins_.push_back(element);
    } else {
      queue_.push(element);
      while (!mins_.empty() && mins_.back() > element) {
        mins_.pop_back();
      }
      mins_.push_back(element);
    }
  }

  void pop() {
    if (queue_.front() == mins_.front()) {
      queue_.pop();
      mins_.pop_front();
    } else {
      queue_.pop();
    }
  }

  T getMin() { return mins_.front(); }

  [[nodiscard]] size_t size() const noexcept { return queue_.size(); }

private:
  std::queue<T> queue_;
  std::deque<T> mins_;
};

void MinLMatrix(std::istream &in, std::ostream &out) {
  size_t n, L;
  in >> n >> L;
  if (n == 0 || L == 0)
    return;
  std::vector<std::vector<std::int32_t>> matrix(n,
                                                std::vector<std::int32_t>(n));
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      in >> matrix[i][j];
    }
  }
  for (size_t i = 0; i < n; ++i) {
    auto deq = MinQueue<int>();
    for (size_t j = 0; j < L; ++j) {
      deq.push(matrix[i][j]);
    }
    matrix[i][0] = deq.getMin();
    for (size_t j = L; j < n; ++j) {
      deq.pop();
      deq.push(matrix[i][j]);
      matrix[i][j - L + 1] = deq.getMin();
    }
  }
  for (size_t j = 0; j < n - L + 1; ++j) {
    auto deq = MinQueue<int>();
    for (size_t i = 0; i < L; ++i) {
      deq.push(matrix[i][j]);
    }
    matrix[0][j] = deq.getMin();
    for (size_t i = L; i < n; ++i) {
      deq.pop();
      deq.push(matrix[i][j]);
      matrix[i - L + 1][j] = deq.getMin();
    }
  }
  bool first = true;
  for (size_t i = 0; i < n - L + 1; ++i) {
    for (size_t j = 0; j < n - L + 1; ++j) {
      out << (first ? "" : " ") << matrix[i][j];
      first = false;
    }
    if (i != n - L) {
      out << '\n';
    }
    first = true;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  MinLMatrix(std::cin, std::cout);
}
