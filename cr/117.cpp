#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  int k, n;
  in >> k;
  for (size_t t = 0; t < k; t++) {
    int starts[10005]{0};
    int ends[10005]{0};
    in >> n;
    int l, r;
    int first = 0, second = 0;
    bool err = false;
    for (size_t i = 1; i <= n; i++) {
      in >> l >> r;
      if (starts[l] != 0 || ends[r] != 0 || l == r) {
        err = true;
      }
      starts[l] = i;
      ends[r] = i;
    }
    if (err || starts[0] == 0)
      goto err;
    first = starts[0];
    for (size_t i = 1; i < 10000; i++) {
      if (starts[i] != 0 && ends[i] != 0) {
        if (ends[i] == second)
          goto err;
        first = second == 0 ? starts[i] : second;
        second = second == 0 ? 0 : starts[i];
        continue;
      }
      if (ends[i] != 0) {
        if (second == 0 || ends[i] == second)
          goto err;
        first = second;
        second = 0;
      }
      if (starts[i] != 0) {
        if (second != 0)
          goto err;
        second = starts[i];
      }
    }
    if (first == 0)
      goto err;

    out << "Accepted\n";
    continue;
  err:
    out << "Wrong Answer\n";
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
  vector<string> inputs{"2 3 0 3000 2500 7000 2700 10000 2 0 3000 2700 10000 "};
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
