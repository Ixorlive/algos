
#include <algorithm>
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;
stack<pair<int, int>> s1, s2;

int min() {
  if (s1.empty() || s2.empty())
    return s1.empty() ? s2.top().second : s1.top().second;
  return min(s1.top().second, s2.top().second);
}

void add(int el) {
  int minima = s1.empty() ? el : min(el, s1.top().second);
  s1.push(make_pair(el, minima));
}

int pop() {
  if (s2.empty())
    while (!s1.empty()) {
      int el = s1.top().first;
      s1.pop();
      int minima = s2.empty() ? el : min(el, s2.top().second);
      s2.push(make_pair(el, minima));
    }
  int result = s2.top().first;
  s2.pop();
  return result;
}

void solve(istream &in, std::ostream &out) {
  long n, k;
  in >> n >> k;
  long el;
  in >> el;
  add(el);
  long m = 0;
  for (size_t i = 1; i < n; i++) {
    in >> el;
    m = max(m, el - min());
    add(el);
    if (i >= k) {
      pop();
    }
  }
  out << m;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{" 5 2 1 2 3 4 5 "};
  int i = -1;
  if (i == -1) {
    for (int i = 0; i < inputs.size(); ++i) {
      istringstream in(inputs[i]);
      ostringstream out;
      solve(in, out);
      cout << "+==== Test #" << i + 1 << " ====+\n";
      cout << out.str();
      cout << "\n";
    }
  } else {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
