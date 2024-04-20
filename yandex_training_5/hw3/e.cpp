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
  int n, a;
  unordered_set<int> s1, s2;
  set<int> res;
  in >> n;
  for (size_t j = 0; j < n; j++) {
    in >> a;
    s1.insert(a);
  }
  in >> n;
  for (size_t i = 0; i < n; i++) {
    in >> a;
    if (s1.find(a) != s1.end()) {
      res.insert(a);
    } else {
      s2.insert(a);
    }
  }
  in >> n;
  for (size_t i = 0; i < n; i++) {
    in >> a;
    if (s1.find(a) != s1.end() || s2.find(a) != s2.end()) {
      res.insert(a);
    }
  }
  copy(res.begin(), res.end(), ostream_iterator<int>(out, " "));
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"2 3 1 2 1 3 2 1 2 ", "3 1 2 2 3 3 4 3 1 5"};
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
