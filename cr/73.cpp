#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

double mx[2][3];
inline bool eq(double a, double b) {
  constexpr double eps = 1e-6;
  return fabs(a - b) < eps;
}
inline bool iszero(double a) { return eq(a, 0.0); }

void solve(istream &in, std::ostream &out) {
  double a, b, c, d, e, f;
  in >> a >> b >> c >> d >> e >> f;
  out << fixed << setprecision(5);
  auto D = a * d - b * c;
  auto dx = e * d - b * f;
  auto dy = a * f - c * e;
  double x, y;
  if (!iszero(D)) {
    out << 2 << ' ' << dx / D << ' ' << dy / D;
  } else {
    if (iszero(dx) && iszero(dy)) {
      if (iszero(a) && iszero(b) && iszero(c) && iszero(d)) {
        out << ((e != 0 || f != 0) ? 0 : 5);
      } else if (iszero(a) && iszero(c)) {
        y = b != 0 ? e / b : f / d;
        out << 4 << ' ' << y;
      } else if (iszero(b) && iszero(d)) {
        x = a != 0 ? e / a : f / c;
        out << 3 << ' ' << x;
      } else {
        double k, q;
        if (b != 0) {
          q = e / b;
          k = -a / b;
        } else {
          q = f / d;
          k = -c / d;
        }
        out << 1 << ' ' << k << ' ' << q;
      }
    } else {
      out << 0;
    }
  }
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{"1 0 0 1 3 3 ", "1 1 2 2 1 2 ", "0 2 0 4 1 2 "};
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
