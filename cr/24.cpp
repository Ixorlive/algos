#include <bits/stdc++.h>

using namespace std;

struct bus {
  int tid, end;
};

int r[1000005];

void solve(istream &in, std::ostream &out) {
  int k, n;
  in >> k >> n;
  vector<int> q(k);
  iota(q.begin(), q.end(), 1);
  priority_queue<int, vector<int>, greater<int>> free(q.begin(), q.end());
  auto c = [](const bus &b1, const bus &b2) { return b1.end > b2.end; };
  priority_queue<bus, vector<bus>, decltype(c)> bs(c);
  int s, e;
  for (size_t i = 0; i < n; i++) {
    in >> s >> e;
    while (!bs.empty() && bs.top().end < s) {
      auto b = bs.top();
      free.push(b.tid);
      bs.pop();
    }
    if (free.empty()) {
      int res = i + 1;
      for (size_t j = i + 1; j < n; j++) {
        in >> s >> e;
      }
      out << 0 << ' ' << res;
      return;
    }
    auto tid = free.top();
    r[i + 1] = tid;
    free.pop();
    bs.push({tid, e});
  }
  copy(r + 1, r + n + 1, ostream_iterator<int>(out, "\n"));
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{"1 1 2 5 ", "1 2 2 5 5 6 ", "1 2 2 5 6 9",
                        "3 4 1 9 2 6 3 7 7 9"};
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
