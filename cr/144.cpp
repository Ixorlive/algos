#include <bits/stdc++.h>

using namespace std;

int res[100005]{0};

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  stack<pair<int, int>> s;
  int a;
  for (size_t i = 0; i < n; i++) {
    in >> a;
    while (!s.empty() && s.top().first > a) {
      res[s.top().second] = i;
      s.pop();
    }
    s.push({a, i});
  }
  while (!s.empty()) {
    res[s.top().second] = -1;
    s.pop();
  }
  copy(res, res + n, ostream_iterator<int>(out, " "));
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{"10 1 2 3 2 1 4 2 5 3 1 "};
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
  } else if (i >= 0 && i < inputs.size()) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  } else {
    cout << "Incorrect test id";
  }
}
