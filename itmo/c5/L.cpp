#include <bits/stdc++.h>
using namespace std;

#define ll long long

const int mod = 7340033;
const int root = 5;
const int root_1 = 4404020;
const int root_pw = 1 << 20;

constexpr int kM = 1 << 17;

constexpr int p = 7;

int a[kM]{0};
int b[kM]{0};
int y[kM]{0};
int T[kM * 4]{0};
int n, m;

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

void fft(int *a, int n, bool invert) {
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

int mult(int a[], int n, int b[], int m, int *res) {
  auto c = 1;
  while (c <= n + m)
    c <<= 1;
  int *afft = new int[c]{0};
  int *bfft = new int[c]{0};
  memcpy(afft, a, sizeof(int) * n);
  memcpy(bfft, b, sizeof(int) * m);
  fft(afft, c, false);
  fft(bfft, c, false);
  for (size_t i = 0; i < c; i++) {
    res[i] = (1ll * afft[i] * bfft[i]) % mod;
  }
  fft(res, c, true);
  for (size_t i = 0; i < c; i++) {
    res[i] = res[i] % p;
    if (res[i] < 0)
      res[i] += p;
  }
  delete[] afft;
  delete[] bfft;
  return c;
}

void inv(int a[], int n, int *res) {
  if (n == 1) {
    res[0] = modInverse(a[0], p);
    return;
  }
  int m = (n + 1) / 2;
  inv(a, m, res);
  int c = mult(res, m, a, n, T);
  memset(T + n, 0, sizeof(int) * (c - n));
  for (size_t i = m; i <= n - 1; i++) {
    if (T[i] != 0)
      T[i] = p - T[i];
  }
  c = mult(res, m, T + m, n - m, res + m);
  memset(res + n, 0, sizeof(int) * (c - n));
}

void sub(int *a, int n, int *b, int m) {
  auto s = min(n, m);
  for (size_t i = 0; i < s; i++) {
    a[i] -= b[i];
    if (a[i] < 0)
      a[i] += p;
  }
}

void solve(istream &in, ostream &out) {
  in >> n;
  for (size_t i = 0; i <= n; i++) {
    in >> a[i];
  }
  in >> m;
  for (size_t i = 0; i <= m; i++) {
    in >> b[i];
  }
  int k = n - m;
  if (k < 0) {
    out << "0 0\n";
    out << n << " ";
    for (size_t i = 0; i <= n; i++) {
      out << a[i] << " ";
    }
    return;
  }
  if (m == 0) {
    auto inv_b = modInverse(b[0], p);
    out << n << " ";
    for (size_t i = 0; i <= n; i++) {
      out << a[i] * inv_b % p << " ";
    }
    out << "\n0 0";
    return;
  }
  ++n, ++m;
  inv(b, k + 1, y);
  int c = mult(a, n, y, k + 1, T);
  memset(T + k + 1, 0, sizeof(int) * (c - k - 1));
  int deg = k;
  while (deg > 0 && T[deg] == 0)
    --deg;
  reverse(T, T + deg + 1);
  if (k - deg > 0) {
    memmove(T + k - deg, T, sizeof(int) * (deg + 1));
    memset(T, 0, sizeof(int) * (k - deg));
    deg = k;
  }
  reverse(b, b + m);
  reverse(a, a + n);
  mult(T, deg + 1, b, m, y);
  sub(a, n, y, deg + m + 1);
  out << deg << " ";
  for (int i = deg; i >= 0; --i) {
    out << T[i] << " ";
  }
  deg = n - 1;
  for (; deg > 0 && a[deg] == 0; --deg) {
  }
  out << '\n' << deg << " ";
  for (int i = deg; i >= 0; --i) {
    out << a[i] << " ";
  }
}
void run_test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  // run_test();
  solve(cin, cout);
  return 0;
}
void run_test() {
  vector<string> inputs = {
      string("3 1 1 1 1\n1 1 1"),
      string("3 1 1 3 1\n2 1 1 1"),
      string("8 2 1 2 1 2 1 2 1 2\n4 1 2 3 4 5"),
  };
  auto outputs = {0};
  for (auto &input : inputs) {
    std::istringstream in(input);
    std::ostringstream out;
    solve(in, out);
    std::cout << out.str() << '\n';
  }
};
