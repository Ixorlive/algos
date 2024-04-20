#include <algorithm>
#include <iostream>
#include <iterator>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

struct St {
  int x, v, id;
};

St arr[100000 + 10];
int res[100000 + 10];

void solve(istream &in, std::ostream &out) {
  int n, d;
  in >> n >> d;
  for (size_t i = 0; i < n; i++) {
    in >> arr[i].x;
    arr[i].id = i;
  }
  sort(arr, arr + n, [](auto &s1, auto &s2) { return s1.x < s2.x; });
  int v = 1;
  arr[0].v = v;
  int prev = 0;
  priority_queue<int, vector<int>, greater<>> vs;
  for (size_t i = 1; i < n; i++) {
    while (arr[i].x - arr[prev].x > d) {
      vs.push(arr[prev].v);
      ++prev;
    }
    if (vs.empty()) {
      vs.push(++v);
    }
    arr[i].v = vs.top();
    vs.pop();
  }
  for (size_t i = 0; i < n; i++) {
    res[arr[i].id] = arr[i].v;
  }
  out << v << '\n';
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
  vector<string> inputs{"4 1 11 1 12 2 ", "4 0 11 1 12 2 "};
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
