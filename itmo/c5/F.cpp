#include <algorithm>
#include <cassert>
#include <cmath>
#include <complex>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
using vi = vector<int>;
using cd = complex<double>;
using vcd = vector<cd>;
const double PI = acos(-1);

void fft(vcd &a, bool invert) {
  size_t s = a.size();
  if (s == 1)
    return;
  vcd a0(s / 2), a1(s / 2);
  for (int i = 0; i < s / 2; ++i) {
    a0[i] = a[i * 2];
    a1[i] = a[i * 2 + 1];
  }
  fft(a0, invert);
  fft(a1, invert);
  double ang = 2 * PI / s * (invert ? -1 : 1);
  cd w(1), wn(cos(ang), sin(ang));
  for (int i = 0; i < s / 2; ++i) {
    a[i] = a0[i] + w * a1[i];
    a[i + s / 2] = a0[i] - w * a1[i];
    if (invert) {
      a[i] /= 2;
      a[i + s / 2] /= 2;
    }
    w *= wn;
  }
}

vector<int> multiply(const vi &a, const vi &b) {
  vcd fa(a.begin(), a.end()), fb(b.begin(), b.end());
  int n = 1;
  while (n < a.size() + b.size())
    n <<= 1;
  fa.resize(n);
  fb.resize(n);
  fft(fa, false);
  fft(fb, false);
  for (int i = 0; i < n; ++i)
    fa[i] *= fb[i];
  fft(fa, true);
  vi res(n);
  for (int i = 0; i < n; ++i)
    res[i] = round(fa[i].real());
  return res;
}

void Multiply(std::istream &in, std::ostream &out) {
  string num1, num2;
  in >> num1 >> num2;
  vi a(num1.rbegin(), num1.rend()), b(num2.rbegin(), num2.rend());
  if (b.size() > a.size()) {
    swap(a, b);
  }
  for (size_t i = 0; i < b.size(); ++i) {
    a[i] -= '0';
    b[i] -= '0';
  }
  for (size_t i = b.size(); i < a.size(); ++i) {
    a[i] -= '0';
  }
  vi result = multiply(a, b);
  int carry = 0;
  for (int &i : result) {
    i += carry;
    carry = i / 10;
    i %= 10;
  }
  while (result.size() > 1 && result.back() == 0) {
    result.pop_back();
  }
  reverse(result.begin(), result.end());
  for (int i : result) {
    out << i;
  }
  //  out << endl;
}

void Test(){{std::istringstream in{"2\n"
                                   "2"};
std::ostringstream out;
Multiply(in, out);
//    cout << out.str();
assert(out.str() == "4");
}
{
  std::istringstream in{"6740948824\n"
                        "9517115276"};
  std::ostringstream out;
  Multiply(in, out);
  //    cout << out.str();
  assert(out.str() == "64154387027624635424");
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //  Test();
  Multiply(std::cin, std::cout);
  return 0;
}
