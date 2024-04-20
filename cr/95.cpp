#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1e5;
size_t arr[MAXN]{0};

void solve(istream &in, std::ostream &out) {
  size_t n, k;
  in >> n >> k;
  for (size_t i = 0; i < n; i++) {
    in >> arr[i];
  }
  int l = 0;
  sort(arr, arr + n);
  unordered_map<int, int> m;
  size_t moretwo = 0;
  size_t res = 0;
  for (size_t i = 0; i < n; i++) {
    while (arr[l] * k < arr[i]) {
      auto v = arr[l];
      if (m[v] > 1) {
        moretwo--;
      }
      l += m[v];
      m.erase(v);
    }
    int p = 1;
    while (i + 1 < n && arr[i] == arr[i + 1]) {
      ++p;
      ++i;
    }
    m[arr[i]] = p;
    if (i - l < 2) {
      moretwo += p >= 2 ? 1 : 0;
      continue;
    }
    if (p >= 3)
      ++res;
    auto uniq = m.size() - 1;
    res += 3 * uniq * (uniq - 1);
    res += 3 * moretwo;
    if (p >= 2) {
      res += 3 * uniq;
      ++moretwo;
    }
  }
  out << res;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"5 2 1 1 2 2 3 "};
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
