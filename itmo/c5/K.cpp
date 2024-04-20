#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using std::cout;

using namespace std;

constexpr double eps = 1e-8;
constexpr int kM = 100 + 10;

double a[kM][kM];
double res[kM]{0};
struct action {
  int i;
  bool b;
};
action y[kM];
action x[kM];
int n;

void prepare() {
  for (int i = 0; i < n; i++) {
    y[i] = {i, false};
    x[i] = {i, true};
  }
  double offset = a[0][0];
  for (size_t i = 1; i < n; i++) {
    if (a[0][i] < offset)
      offset = a[0][i];
  }
  offset -= 1;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      a[i][j] -= offset;
    }
  }
}

void simplex() {
  int i, j, p, q;
  double r;
  while (true) {
    q = -1;
    for (size_t i = 0; i < n; i++) {
      if (a[n][i] < 0) {
        q = i;
        break;
      }
    }
    if (q < 0)
      break;
    r = 0.0;
    for (size_t i = 0; i < n; i++) {
      if (a[i][q] > eps) {
        if (a[i][n] < 0) {
          p = i;
          break;
        } else if (a[i][q] > a[i][n] * r) {
          p = i;
          r = a[i][q] / a[i][n];
        }
      }
    }

    for (i = 0; i < p; i++) {
      for (j = 0; j < q; j++) {
        a[i][j] -= a[p][j] * a[i][q] / a[p][q];
      }
      for (j = q + 1; j < n + 1; j++) {
        a[i][j] -= a[p][j] * a[i][q] / a[p][q];
      }
    }
    for (i = p + 1; i < n + 1; i++) {
      for (j = 0; j < q; j++) {
        a[i][j] -= a[p][j] * a[i][q] / a[p][q];
      }
      for (j = q + 1; j < n + 1; j++) {
        a[i][j] -= a[p][j] * a[i][q] / a[p][q];
      }
    }

    for (i = 0; i < p; i++) {
      a[i][q] /= -a[p][q];
    }
    for (i = p + 1; i < n + 1; i++) {
      a[i][q] /= -a[p][q];
    }
    for (j = 0; j < q; ++j) {
      a[p][j] /= a[p][q];
    }
    for (j = q + 1; j < n + 1; ++j) {
      a[p][j] /= a[p][q];
    }

    a[p][q] = 1 / a[p][q];
    swap(x[p], y[q]);
  }
}

void opt() {
  for (size_t i = 0; i < n; i++) {
    if (!x[i].b)
      res[x[i].i] = a[i][n] / a[n][n];
  }
}

void solve(istream &in, std::ostream &out) {
  in >> n;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      in >> a[i][j];
    }
    a[i][n] = 1;
    a[n][i] = -1;
  }
  a[n][n] = 0;
  prepare();
  simplex();
  opt();
  for (size_t i = 0; i < n; i++) {
    out << res[i] << "\n";
  }
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  cout.setf(std::ios::fixed, std::ios::floatfield);
  cout << std::setprecision(9);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{
      "3 1000 10 10 0 1000 1 5 3 1000",
      "5 1000 0 0 0 0 0 1000 0 0 0 0 0 1000 0 0 0 0 0 1000 0 0 0 0 0 1000"};
  for (const auto &input : inputs) {
    istringstream in(input);
    ostringstream out;
    out.setf(std::ios::fixed, std::ios::floatfield);
    out << std::setprecision(9);
    solve(in, out);
    cout << out.str();
  }
}
