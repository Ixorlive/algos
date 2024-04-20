#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  queue<int> q;
  int n, k, a;
  in >> n >> k;
  k = min(n, k);
  unordered_set<int> s;
  for (size_t i = 0; i < k; i++) {
    in >> a;
    if (s.find(a) != s.end()) {
      out << "YES";
      return;
    }
    s.insert(a);
    q.push(a);
  }
  for (size_t i = 0; i < n - k; i++) {
    in >> a;
    if (s.find(a) != s.end()) {
      out << "YES";
      return;
    }
    s.insert(a);
    q.push(a);
    auto t = q.front();
    s.erase(t);
    q.pop();
  }
  out << "NO";
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{" 4 2 1 2 3 1 ", "4 1 1 0 1 1", "6 2 1 2 3 1 2 3",
                        "10 20 1 2 3 4 5 6 7 8 9 10"};
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
