#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

char buf[100000];
void solve(istream &in, std::ostream &out) {
  long n;
  in >> n;
  long a;
  in >> a;
  bool cur_res_odd = a % 2 != 0;
  for (size_t i = 0; i < n - 1; i++) {
    in >> a;
    bool is_odd = (a % 2 != 0);
    if (!cur_res_odd) {
      buf[i] = '+';
      cur_res_odd = (a % 2 != 0);
    } else {
      if (is_odd) {
        buf[i] = 'x';
      } else {
        buf[i] = '+';
      }
    }
  }
  buf[n - 1] = '\0';
  out << buf;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"3 5 7 2", "2 4 -5"};
  for (int i = 0; i < inputs.size(); ++i) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
