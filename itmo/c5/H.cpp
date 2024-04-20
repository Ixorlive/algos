#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define ll long long

constexpr int mod = 786433;
constexpr int root = 108788;
constexpr int root_1 = 295516;
constexpr int root_pw = 1 << 16;

int n, h;

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

void fft(vector<int> &a, bool invert) {
  int n = (int)a.size();

  for (int i = 1, j = 0; i < n; ++i) {
    int bit = n >> 1;
    for (; j >= bit; bit >>= 1)
      j -= bit;
    j += bit;
    if (i < j)
      swap(a[i], a[j]);
  }

  for (int len = 2; len <= n; len <<= 1) {
    int wlen = invert ? root_1 : root;
    for (int i = len; i < root_pw; i <<= 1)
      wlen = int(wlen * 1ll * wlen % mod);
    for (int i = 0; i < n; i += len) {
      int w = 1;
      for (int j = 0; j < len / 2; ++j) {
        int u = a[i + j], v = int(a[i + j + len / 2] * 1ll * w % mod);
        a[i + j] = u + v < mod ? u + v : u + v - mod;
        a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
        w = int(w * 1ll * wlen % mod);
      }
    }
  }
  if (invert) {
    int nrev = modInverse(n, mod);
    for (int i = 0; i < n; ++i)
      a[i] = int(a[i] * 1ll * nrev % mod);
  }
}

void solve(istream &in, ostream &out) {
  in >> n >> h;
  std::vector<ll> gk_values(root_pw);
  gk_values[0] = 1;
  ll v = root;
  for (int k = 1; k < root_pw; ++k) {
    gk_values[k] = v;
    v = (v * root) % mod;
  }
  std::vector<int> D0(root_pw, 0), D1(root_pw, 0), D2(root_pw, 0);
  D0[0] = 1;
  D1[1] = 1;

  fft(D0, false);
  fft(D1, false);

  std::vector<int> *pD0 = &D0;
  std::vector<int> *pD1 = &D1;
  std::vector<int> *pD2 = &D2;

  for (int i = 1; i <= h; ++i) {
    for (int k = 0; k < root_pw; ++k) {
      (*pD2)[k] =
          (((1LL * (*pD1)[k] * (*pD1)[k] + 2LL * (*pD1)[k] * (*pD0)[k]) % mod) *
           gk_values[k]) %
          mod;
    }

    swap(pD0, pD1);
    swap(pD1, pD2);
  }

  fft(*pD1, true);

  out << (*pD1)[n];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //    Test();
  solve(cin, cout);
  // cout << fast_power(10, (mod - 1) / root_pw, mod) << '\n' <<
  // modInverse(108788, mod);
  return 0;
}
