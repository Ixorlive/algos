#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  int n, k;
  string s;
  in >> n >> k;
  unordered_set<string> s1, s2;
  for (size_t i = 0; i < k; i++) {
    in >> s;
    s1.insert(s);
  }
  for (size_t i = 0; i < n - 1; i++) {
    in >> k;
    for (size_t j = 0; j < k; j++) {
      in >> s;
      if (s1.find(s) != s1.end()) {
        s2.insert(s);
      }
    }
    swap(s1, s2);
    s2.clear();
  }
  set<string> s3(s1.begin(), s1.end());
  out << s3.size() << '\n';
  copy(s3.begin(), s3.end(), ostream_iterator<string>(out, " "));
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"1 2 GoGetIt Life ", "2 2 Love Life 2 Life GoodDay "};
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
  } else {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
