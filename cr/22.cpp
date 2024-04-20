#include <algorithm>
#include <iostream>
#include <optional>
#include <stack>
#include <utility>
#include <vector>

using namespace std;

class MinStack {
public:
  void push(int v) {
    if (s.empty())
      s.emplace(v, v);
    else
      s.emplace(v, std::min(v, s.top().second));
  }
  int pop() noexcept {
    int res = s.top().first;
    s.pop();
    return res;
  }
  int min() const noexcept { return s.top().second; }
  bool empty() const noexcept { return s.empty(); }

private:
  stack<pair<int, int>> s;
};

class MinQueue {
private:
  MinStack s1, s2;

public:
  void push(int v) noexcept { s1.push(v); }
  void pop() noexcept {
    if (s2.empty()) {
      while (!s1.empty()) {
        s2.push(s1.pop());
      }
    }
    s2.pop();
  }
  int min() const noexcept {
    if (s1.empty() || s2.empty()) {
      return s1.empty() ? s2.min() : s1.min();
    }
    return std::min(s1.min(), s2.min());
  }
};

int main() {
  int n, k;
  cin >> n >> k;
  MinQueue q;
  for (int i = 0; i < k; ++i) {
    int v;
    cin >> v;
    q.push(v);
  }
  cout << q.min() << ' ';
  for (int i = k; i < n; ++i) {
    int v;
    cin >> v;
    q.pop();
    q.push(v);
    cout << q.min() << ' ';
  }
  return 0;
}
