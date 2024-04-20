#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int arr[100000 + 10];

void solve(istream &in, std::ostream &out) {
  int n, R, c;
  in >> n >> R >> c;
  for (size_t i = 0; i < n; i++) {
    in >> arr[i];
  }
  sort(arr, arr + n);
  auto check = [&](size_t diff) {
    int gs = 0;
    for (size_t i = c - 1; i < n; i++) {
      if (arr[i] - arr[i - c + 1] <= diff) {
        ++gs;
        i += c - 1;
      }
    }
    return gs >= R;
  };
  size_t l = 0;
  size_t r = arr[n - 1] - arr[0];
  while (l < r) {
    size_t m = (l + r) / 2;
    if (!check(m)) {
      l = m + 1;
    } else {
      r = m;
    }
  }
  out << l;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{"8 2 3 170 205 225 190 260 130 225 160 "};
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
