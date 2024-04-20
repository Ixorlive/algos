#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

#define ll long long

constexpr int kM = 315;

ll a[kM][kM];
ll b[kM][kM];
bitset<kM> s;
int n, m, p;
vector<bool> tests = {true, true, true, true, true, true};

void printMs() {
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << a[i][j] << " ";
    }
    cout << '\n';
  }
}

ll modInverse(ll val, ll md) {
  ll m0 = md, t, q;
  ll x0 = 0, x1 = 1;

  if (md == 1)
    return 0;

  while (val > 1) {
    q = val / md;
    t = md;
    md = val % md, val = t;
    t = x0;
    x0 = x1 - q * x0;
    x1 = t;
  }
  if (x1 < 0)
    x1 += m0;

  return x1;
}

auto gauss() -> int {
  int row = 0;
  for (int col = 0; col < n; ++col) {
    if (a[row][col] == 0) {
      for (int i = row + 1; i < m; ++i) {
        if (a[i][col] != 0) {
          swap(a[row], a[i]);
        }
      }
    }
    if (!a[row][col])
      continue;
    s[col] = true;
    ll t = a[row][col];
    ll inverse_t = modInverse(t, p);
    for (int i = col; i < n; ++i) {
      a[row][i] = (a[row][i] * inverse_t) % p;
    }
    for (int i = 0; i < m; ++i) {
      if (i != row && a[i][col] != 0) {
        t = a[i][col];
        for (int j = col; j < n; ++j) {
          a[i][j] = (a[i][j] - ((t * a[row][j]) % p) + p) % p;
        }
      }
    }
    ++row;
  }
  return row;
}

void solve(istream &in, ostream &out) {
  in >> m >> n >> p;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      in >> a[i][j];
      b[i][j] = a[i][j];
    }
  }
  auto k = gauss();
  out << k << '\n';
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (s[j])
        out << b[i][j] << " ";
    }
    out << "\n";
  }
  for (int i = 0; i < k; ++i) {
    for (int j = 0; j < n; ++j) {
      out << a[i][j] << " ";
    }
    out << "\n";
  }
}

void Test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //    Test();
  solve(std::cin, std::cout);
  return 0;
}

void Test(){{if (tests[0]){std::istringstream in{"5 3\n"
                                                 "1 0 0\n"
                                                 "0 1 0\n"
                                                 "0 0 1\n"
                                                 "0 0 2\n"
                                                 "0 0 3\n"
                                                 "10\n"
                                                 "20\n"
                                                 "30\n"
                                                 "10\n"
                                                 "10"};
std::ostringstream out;
solve(in, out);
//            cout << out.str();
assert(out.str() == "40\n"
                    "1\n"
                    "2\n"
                    "4\n");
}
}
{
  if (tests[1]) {
    std::istringstream in{"5 4\n"
                          "1 0 0 0\n"
                          "1 1 0 0\n"
                          "1 1 1 0\n"
                          "1 2 3 0\n"
                          "2 3 4 0\n"
                          "1\n"
                          "1\n"
                          "1\n"
                          "1\n"
                          "1"};
    std::ostringstream out;
    solve(in, out);
    //            cout << out.str();
    assert(out.str() == "0");
  }
  //    assert(out.str() == "4");
}
}
;
