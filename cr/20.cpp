#include <bits/stdc++.h>

using namespace std;

constexpr int MAXN = 1000050;
size_t a[MAXN]{0};
int l[MAXN]{0};
int r[MAXN]{0};
int s[MAXN]{0};

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  int pos = -1;
  for (size_t i = 0; i < n; i++) {
    in >> a[i];
    while (pos != -1 && a[s[pos]] > a[i]) {
      r[s[pos]] = i;
      --pos;
    }
    s[++pos] = i;
  }
  while (pos != -1) {
    r[s[pos]] = n;
    --pos;
  }
  for (int i = n - 1; i >= 0; i--) {
    while (pos != -1 && a[s[pos]] > a[i]) {
      l[s[pos]] = i;
      --pos;
    }
    s[++pos] = i;
  }
  while (pos != -1) {
    l[s[pos]] = -1;
    --pos;
  }
  size_t mmax = 0;
  for (size_t i = 0; i < n; i++) {
    size_t area = a[i] * (r[i] - l[i] - 1);
    mmax = max(mmax, area);
  }
  out << mmax;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"7 2 1 4 5 1 3 3"};
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
