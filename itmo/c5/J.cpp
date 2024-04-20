#include <cmath>
#include <complex>
#include <iostream>
#include <vector>

using namespace std;

constexpr int MAXN = 131072;
#define PI 3.141593f

int M;

typedef complex<double> base;

void fft(vector<base> &a, bool invert) {
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
    double ang = 2 * PI / len * (invert ? -1 : 1);
    base wlen(cos(ang), sin(ang));
    for (int i = 0; i < n; i += len) {
      base w(1);
      for (int j = 0; j < len / 2; ++j) {
        base u = a[i + j], v = a[i + j + len / 2] * w;
        a[i + j] = u + v;
        a[i + j + len / 2] = u - v;
        w *= wlen;
      }
    }
  }
  if (invert)
    for (int i = 0; i < n; ++i)
      a[i] /= n;
}

void solve(istream &in, ostream &out) {
  in >> M;
  string str1, str2;
  in >> str1 >> str2;

  vector<base> a1(M, 0), a2(M, 0), c1(M, 0), c2(M, 0), g1(M, 0), g2(M, 0),
      t1(M, 0), t2(M, 0), res(M, 0);

  for (int i = 0; i < M; ++i) {
    char c = str1[i];
    if (c == 'A')
      a1[i] = 1;
    else if (c == 'C')
      c1[i] = 1;
    else if (c == 'G')
      g1[i] = 1;
    else if (c == 'T')
      t1[i] = 1;
  }

  a2[0] = (str2[0] == 'A');
  c2[0] = (str2[0] == 'C');
  g2[0] = (str2[0] == 'G');
  t2[0] = (str2[0] == 'T');
  for (int i = 1; i < M; ++i) {
    char c = str2[M - i];
    if (c == 'A')
      a2[i] = 1;
    else if (c == 'C')
      c2[i] = 1;
    else if (c == 'G')
      g2[i] = 1;
    else if (c == 'T')
      t2[i] = 1;
  }

  fft(a1, false);
  fft(a2, false);
  fft(c1, false);
  fft(c2, false);
  fft(g1, false);
  fft(g2, false);
  fft(t1, false);
  fft(t2, false);

  for (int i = 0; i < M; ++i) {
    a1[i] *= a2[i];
    c1[i] *= c2[i];
    g1[i] *= g2[i];
    t1[i] *= t2[i];
  }

  vector<base> result(M, 0);
  for (int i = 0; i < M; ++i) {
    result[i] = a1[i] + c1[i] + g1[i] + t1[i];
  }

  fft(result, true);
  int max_shift = 0;
  double max_v = result[0].real();
  for (int i = 1; i < M; ++i) {
    auto sum = result[i].real();
    if (sum > max_v) {
      max_shift = i;
      max_v = sum;
    }
  }
  out << int(max_v + 0.5) << " " << max_shift;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  solve(cin, cout);
  return 0;
}
