#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

using ll = unsigned long long;

int polk[2 * 100000 + 5];
ll prefix[2 * 100000 + 5];
// while (l < r) {
//   ll m = l + (r - l + 1) / 2;
//   if (f(m) <= n) {
//     l = m;
//   } else {
//     r = m - 1;
//   }
// }
void solve(istream &in, std::ostream &out) {
  int n, m;
  in >> n >> m;
  for (size_t i = 0; i < n; i++) {
    in >> polk[i];
  }
  prefix[0] = 0;
  for (size_t i = 1; i <= n; i++) {
    prefix[i] = prefix[i - 1] + polk[i - 1];
  }
  int c;
  ll s;
  int l, r;
  for (size_t i = 0; i < m; i++) {
    in >> c >> s;
    int l = 0, r = n - c;
    bool found = false;
    while (l <= r) {
      int mid = l + (r - l) / 2;
      ll sum = prefix[mid + c] - prefix[mid];
      if (sum == s) {
        found = true;
        r = mid - 1;
      } else if (sum < s) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    out << (found ? l + 1 : -1) << '\n';
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
  vector<string> inputs{"5 2 1 3 5 7 9 2 4 1 3 "};
  // vector<string> inputs({"6265505"});
  for (int i = 0; i < inputs.size(); ++i) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
