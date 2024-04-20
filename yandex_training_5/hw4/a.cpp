#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int arr[100004];

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  for (size_t i = 0; i < n; i++) {
    in >> arr[i];
  }
  sort(arr, arr + n);
  int k;
  in >> k;
  int l, r;
  for (size_t i = 0; i < k; i++) {
    in >> l >> r;
    auto cnt_l = lower_bound(arr, arr + n, l);
    auto cnt_r = upper_bound(arr, arr + n, r);
    out << cnt_r - cnt_l << ' ';
  }
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"5 10 1 10 3 4 4 1 10 2 9 3 4 2 2"};
  for (int i = 0; i < inputs.size(); ++i) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
