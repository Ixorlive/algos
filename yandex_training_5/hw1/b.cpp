#include <iostream>
#include <sstream>

using namespace std;

void solve(ostream &out, istream &in) {
  long g1, g2, g3, g4, q;
  char c;
  in >> g1 >> c >> g2 >> g3 >> c >> g4 >> q;

  if (g1 + g3 > g2 + g4) {
    out << 0;
  } else {
    int k = g2 + g4 - g1 - g3;
    if (q == 1) {
      out << (g3 + k > g2 ? k : k + 1);
    } else {
      out << (g1 > g4 ? k : k + 1);
    }
  }
}

void test() {
  {
    istringstream in("0:0 0:0 1");
    ostringstream out;
    solve(out, in);
    cout << out.str() << '\n';
  }
  {
    istringstream in("0:2 0:3 1");
    ostringstream out;
    solve(out, in);
    cout << out.str() << '\n';
  }
  {
    istringstream in("0:2 0:3 2");
    ostringstream out;
    solve(out, in);
    cout << out.str() << '\n';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // test();

  solve(cout, cin);

  return 0;
}
