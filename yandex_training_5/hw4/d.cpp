#include <algorithm>
#include <climits>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

using ll = unsigned long long;

constexpr int MAX_LEN = 100005;
int as[MAX_LEN];
int bs[MAX_LEN];

ll get_lines(int *arr, int size, int w) {
  ll lines = 1;
  ll cur_w = 0;
  for (size_t i = 0; i < size; ++i) {
    auto wl = arr[i];
    if (cur_w == 0 || cur_w + wl + 1 <= w) {
      cur_w += cur_w == 0 ? wl : wl + 1;
    } else {
      ++lines;
      cur_w = wl;
    }
  }
  return lines;
}
// while (l < r) {
//   ll m = l + (r - l + 1) / 2;
//   if (f(m) <= n) {
//     l = m;
//   } else {
//     r = m - 1;
//   }
// }
void solve(istream &in, std::ostream &out) {
  int w, alen, blen;
  in >> w >> alen >> blen;
  int max_a = -1, max_b = -1;
  for (size_t i = 0; i < alen; i++) {
    in >> as[i];
    max_a = max(as[i], max_a);
  }
  for (size_t i = 0; i < blen; i++) {
    in >> bs[i];
    max_b = max(bs[i], max_b);
  }
  int l = max_a;
  int r = w - max_b;
  ll mmin = LONG_MAX;
  while (l <= r) {
    int m = l + (r - l) / 2;
    auto la = get_lines(as, alen, m);
    auto lb = get_lines(bs, blen, w - m);
    mmin = min(max(la, lb), mmin);
    if (la == lb) {
      l = m;
      break;
    }
    if (la > lb) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  out << mmin;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{" 15 6 6 2 2 2 3 2 2 3 3 5 2 4 3 ",
                        "10 5 5 1 1 2 1 2 7 7 1 5 5"};
  // vector<string> inputs({"6265505"});
  int i = 1;
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
