#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Jewels {
  int v;
  int w;
  int i;
  double coeff;
  bool operator<(const Jewels &j) const { return coeff > j.coeff; }
};

void K_best(istream &in, ostream &out) {
  int n, k;
  in >> n >> k;
  vector<Jewels> js(n);
  for (int i = 0; i < n; ++i) {
    in >> js[i].v >> js[i].w;
    js[i].i = i + 1;
  }
  auto get_coef = [&]() {
    int x1 = 0, x2 = 0;
    for_each(js.begin(), js.begin() + k, [&](const auto &j) {
      x1 += j.v;
      x2 += j.w;
    });
    return (double)x1 / (double)x2;
  };
  double s1, s2;
  s1 = get_coef();
  do {
    s2 = s1;
    for (int i = 0; i < n; ++i) {
      js[i].coeff = js[i].v - s1 * js[i].w;
    }
    sort(js.begin(), js.end());
    s1 = get_coef();
  } while (fabs(s2 - s1) > 0);
  for_each(js.begin(), js.begin() + k - 1,
           [&](const auto &j) { out << j.i << " "; });
  out << js[k - 1].i;
}

void Test() {
  {
    istringstream in("3 2\n"
                     "1 1\n"
                     "1 2\n"
                     "1 3");
    ostringstream out;
    K_best(in, out);
    cout << out.str();
  }
  {
    istringstream in("10 4\n"
                     "1 2\n"
                     "2 3\n"
                     "3 4\n"
                     "4 5\n"
                     "5 6\n"
                     "6 7\n"
                     "7 8\n"
                     "8 9\n"
                     "9 10\n"
                     "10 11");
    ostringstream out;
    K_best(in, out);
    cout << out.str();
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //    Test();
  K_best(cin, cout);
}
