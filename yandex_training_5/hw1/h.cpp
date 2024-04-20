#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  long L_i, x1_i, x2_i, v1_i, v2_i;
  in >> L_i >> x1_i >> v1_i >> x2_i >> v2_i;
  x1_i %= L_i;
  x2_i %= L_i;
  if (v2_i < 0 && v1_i < 0) {
    x1_i = L_i - x1_i;
    x2_i = L_i - x2_i;
    v1_i *= -1;
    v2_i *= -1;
  }
  if (v1_i == 0 && v2_i == 0 && x1_i != x2_i) {
    out << "NO";
    return;
  }
  if (x1_i == x2_i) {
    out << "YES\n0.0000000000";
    return;
  }
  double L = L_i;
  double x1 = x1_i;
  double x2 = x2_i;
  double v1 = v1_i;
  double v2 = v2_i;
  double t = -1;
  if (x2 < x1) {
    swap(x1, x2);
    swap(v1, v2);
  }
  if (v1 >= 0 && v2 >= 0) {
    if (x1 <= L / 2.0 && x2 <= L / 2.0) {
      if ((L / 2.0 - x1) / v1 < (L / 2.0 - x2) / v2) {
        t = (x2 - x1) / (v1 - v2);
      } else {
        t = (L - x2 - x1) / (v1 + v2);
      }
    } else if (x1 >= L / 2.0 && x2 >= L / 2.0) {
      if ((L - x1) / v1 < (L - x2) / v2) {
        t = (x2 - x1) / (v1 - v2);
      } else {
        t = (2.0 * L - x2 - x1) / (v1 + v2);
      }
    } else if (x1 < L - x2) {
      t = (L - x1 - x2) / (v1 + v2);
    } else {
      if ((L - x1) / v1 < (L - x2) / v2) {
        t = (x2 - x1) / (v1 - v2);
      } else if ((L - x2 + L / 2.0) / v2 < (L / 2.0 - x1) / v1) {
        t = (L - x2 + x1) / (v2 - v1);
      } else {
        t = (2.0 * L - x1 - x2) / (v1 + v2);
      }
    }
  } else {
    if (v1 < 0) {
      swap(x1, x2);
      swap(v1, v2);
    }
    auto v2_a = abs(v2);
    if (x2 < x1) {
      if (x1 >= L / 2.0 || x2 > L / 2.0) {
        x2 = fmod(x2 + L / 2.0, L_i);
        x1 = fmod(x1 + L / 2.0, L_i);
      }
    }
    if (x2 >= x1) {
      if ((x1 <= L / 2.0 && x2 <= L / 2.0) ||
          (x2 >= L / 2.0 && x1 >= L / 2.0)) {
        t = (x2 - x1) / (v1 + v2_a);
      } else if (L - x2 > x1) {
        if ((x2 - L / 2.0) / v2_a < (L / 2.0 - x1) / v1) {
          t = (x2 - x1) / (v1 + v2_a);
        } else {
          t = (L - x1 - x2) / (v1 - v2_a);
        }
      } else {
        if ((x2 - L / 2.0) / v2_a > (L / 2.0 - x1) / v1) {
          t = (x2 - x1) / (v1 + v2_a);
        } else {
          t = (L - x1 - x2) / (v1 - v2_a);
        }
      }
    } else {
      if ((x2 + L / 2.0) / v2_a < (L / 2.0 - x1) / v1) {
        t = (x1 + x2) / (v2_a - v1);
      } else if (x2 / v2_a > (L - x1) / v1) {
        t = (L - x1 - x2) / (v1 - v2_a);
      } else {
        t = (L - x1 + x2) / (v1 + v2_a);
      }
    }
  }
  out << "YES\n" << fixed << setprecision(10) << t;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"6 3 1 1 1", "12 8 10 5 20 ", " 5 0 0 1 2 ",
                        "10 7 -3 1 4"};
  // int i = 1;
  for (int i = 0; i < inputs.size(); ++i) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
