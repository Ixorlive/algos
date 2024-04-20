#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

constexpr int MAXMINS = 24 * 60;
constexpr int MAXN = 1e5;

int freebuss[MAXN + 10]{0};

void solve(istream &in, std::ostream &out) {
  vector<int> starts[MAXMINS * 2];
  vector<int> es[MAXMINS * 2];
  vector<int> es2[MAXMINS * 2];
  int n, m;
  in >> n >> m;
  int h1, h2, m1, m2, from, to;
  char ch;
  for (size_t i = 0; i < m; i++) {
    in >> from >> h1 >> ch >> m1 >> to >> h2 >> ch >> m2;
    auto time1 = h1 * 60 + m1;
    auto time2 = h2 * 60 + m2;
    starts[time1].push_back(from);
    starts[time1 + MAXMINS].push_back(from);
    if (time1 < time2) {
      es[time2].push_back(to);
    }
    es2[time2].push_back(to);
    es2[time2 + MAXMINS].push_back(to);
    es[time2 + MAXMINS].push_back(to);
  }
  size_t totalbs = 0;
  auto f = [&]() {
    for (size_t i = 0; i < MAXMINS * 2; i++) {
      for (int t : es[i]) {
        freebuss[t]++;
      }
      for (int t : starts[i]) {
        if (freebuss[t] == 0) {
          ++totalbs;
        } else {
          freebuss[t]--;
        }
      }
    }
  };
  f();
  swap(es, es2);
  size_t prev = totalbs;
  f();
  if (prev != totalbs) {
    out << -1;
  } else {
    out << totalbs;
  }
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{
      "2 2 2 20:00 1 10:00 1 08:00 2 21:00 ",
      "2 2 1 09:00 2 20:00 2 20:00 1 09:00 ",
      "3 4 3 03:52 1 08:50 1 18:28 3 21:53 2 03:58 3 09:00 3 14:59 2 21:13 ",
      "3 2 1 23.55 2 00.05 2 00.06 3 00.05 "};
  int i = -1;
  if (i == -1) {
    for (int i = 0; i < inputs.size(); ++i) {
      memset(freebuss, 0, sizeof(freebuss));
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
