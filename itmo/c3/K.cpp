#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using D_Matrix = std::vector<std::vector<int>>;

void Floyd(std::istream &in, std::ostream &out) {
  size_t n;
  in >> n;
  D_Matrix d(n, std::vector<int>(n));
  for (size_t i = 0; i < n; ++i) {
    for (size_t j = 0; j < n; ++j) {
      in >> d[i][j];
    }
  }
  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    std::copy(d[i].begin(), d[i].end(), std::ostream_iterator<int>(out, " "));
    if (i != n - 1)
      out << '\n';
  }
}

void Test(){{std::istringstream in("4\n"
                                   "0 5 9 100\n"
                                   "100 0 2 8\n"
                                   "100 100 0 7\n"
                                   "4 100 100 0");
std::ostringstream out;
Floyd(in, out);
//        std::cout << out.str();
assert(out.str() == "0 5 7 13 \n"
                    "12 0 2 8 \n"
                    "11 16 0 7 \n"
                    "4 9 11 0 ");
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //    Test();
  Floyd(std::cin, std::cout);
}
