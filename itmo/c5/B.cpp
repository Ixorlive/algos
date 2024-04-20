#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

using namespace std;

#define MOD 1000000007
#define ll long long

constexpr int kM = 2001;
constexpr int kN = 51;
constexpr double eps = 1e-8;

ll a[kM][kN];
pair<int, int> c[kM];
int n;
int m;
vector<bool> tests = {true, true, true, true, true, true};

bool isZero(double value) { return abs(value) <= eps; }

void printMs() {
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cout << a[i][j] << " ";
    }
    cout << '\n';
  }
  for (int i = 0; i < m; ++i) {
    cout << c[i].first << ' ' << c[i].second << '\n';
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

bool gauss() {
  for (int k = 0; k < n; ++k) {
    int min = k;
    for (int i = k; i < m; ++i) {
      if (a[min][k] == 0 || (a[i][k] != 0 && c[i].second < c[min].second))
        min = i;
    }
    if (a[min][k] == 0) {
      return false;
    }
    swap(a[k], a[min]);
    swap(c[k], c[min]);
    ll t = a[k][k];
    ll inverse_t = modInverse(t, MOD);
    for (int i = k; i < n; ++i) {
      a[k][i] = (a[k][i] * inverse_t) % MOD;
    }
    for (int i = k + 1; i < m; ++i) {
      if (a[i][k] != 0) {
        t = a[i][k];
        for (int j = k; j < n; ++j) {
          a[i][j] = (a[i][j] - ((t * a[k][j]) % MOD) + MOD) % MOD;
        }
      }
    }
  }
  return true;
}

void solve(istream &in, ostream &out) {
  in >> m >> n;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      in >> a[i][j];
    }
  }
  for (int i = 0; i < m; ++i) {
    in >> c[i].second;
    c[i].first = i;
  }
  //    printMs();
  if (n <= m && gauss()) {
    auto res = std::accumulate(
        c, c + n, 0, [](std::int64_t sum, const std::pair<int, int> &p) {
          return sum + p.second;
        });
    out << res << '\n';
    for (int i = 0; i < n; ++i) {
      out << c[i].first + 1 << '\n';
    }
  } else {
    out << 0;
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
{
  if (tests[2]) {
    std::istringstream in{"5 4\n"
                          "1 2 3 4\n"
                          "2 4 5 9\n"
                          "3 6 7 1\n"
                          "1 1 1 9\n"
                          "3 2 1 9\n"
                          "1\n"
                          "2\n"
                          "3\n"
                          "4\n"
                          "5"};
    std::ostringstream out;
    solve(in, out);
    //            cout << out.str();
    assert(out.str() == "10\n"
                        "1\n"
                        "2\n"
                        "3\n"
                        "4\n");
  }
}
{
  if (tests[3]) {
    stringstream in;
    stringstream out;
    in << "6 3\n"
       << "1 0 0\n"
       << "0 1 0\n"
       << "0 0 1\n"
       << "1 1 0\n"
       << "0 1 1\n"
       << "1 0 1\n"
       << "3\n"
       << "2\n"
       << "1\n"
       << "4\n"
       << "5\n"
       << "6\n";
    solve(in, out);
    string expected_output = "6\n1\n2\n3\n";
    assert(out.str() == expected_output);
  }
}
}
;
