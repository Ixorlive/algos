#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

constexpr int maxn = 101;
struct Coord {
  int x, y;
};
Coord mx[maxn];
int n;

void solve(istream &in, std::ostream &out) {
  in >> n;
  for (size_t i = 0; i < n; i++) {
    in >> mx[i].x >> mx[i].y;
    --mx[i].x;
    --mx[i].y;
  }
  int minm = 100500;
  for (int i = 0; i < n; i++) {
    int tm = 0;
    int arr[maxn]{0};
    for (int j = 0; j < n; j++) {
      arr[mx[j].x]++;
      tm += abs(i - mx[j].y);
    }
    int exc = 0;
    for (size_t j = 0; j < n; j++) {
      int move = arr[j] - 1 + exc;
      tm += abs(move);
      exc += arr[j] - 1;
    }
    minm = min(tm, minm);
  }
  out << minm;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{" 3 1 2 3 3 1 1 "};
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
