#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void TransitiveClosure(std::istream &in, std::ostream &out) {
  int n;
  in >> n;
  Graph g(n);
  for (int i = 0; i < n; ++i) {
    std::string row;
    in >> row;
    for (int j = 0; j < n; ++j) {
      if (row[j] == '1')
        g[i].push_back(j);
    }
  }
  std::vector<std::vector<char>> res(n, std::vector<char>(n, '0'));
  for (int i = 0; i < n; ++i) {
    std::vector<int> d(g.size(), 0);
    std::vector<int> stk{i};
    while (!stk.empty()) {
      int u = stk.back();
      stk.pop_back();
      for (const auto &v : g[u]) {
        if (d[v] != 0)
          continue;
        stk.push_back(v);
        res[i][v] = '1';
        d[v] = 1;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    std::copy(res[i].begin(), res[i].end(), std::ostream_iterator<char>(out));
    if (i != n - 1)
      out << '\n';
  }
}

void Test(){{std::istringstream in("3\n"
                                   "010\n"
                                   "001\n"
                                   "000");
std::ostringstream out;
TransitiveClosure(in, out);
//        std::cout << out.str();
assert(out.str() == "011\n"
                    "001\n"
                    "000");
}
{
  std::istringstream in("10\n"
                        "0000000100\n"
                        "1000010011\n"
                        "0000101100\n"
                        "1000000000\n"
                        "0010001100\n"
                        "0100000100\n"
                        "1001000101\n"
                        "1101010101\n"
                        "0000100001\n"
                        "1100000010");
  std::ostringstream out;
  TransitiveClosure(in, out);
  //        std::cout << out.str();
  assert(out.str() == "1111111111\n"
                      "1111111111\n"
                      "1111111111\n"
                      "1111111111\n"
                      "1111111111\n"
                      "1111111111\n"
                      "1111111111\n"
                      "1111111111\n"
                      "1111111111\n"
                      "1111111111");
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //    Test();
  TransitiveClosure(std::cin, std::cout);
}
