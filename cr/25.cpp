#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  priority_queue<size_t, vector<size_t>, greater<size_t>> pq;
  size_t a;
  for (size_t i = 0; i < n; i++) {
    in >> a;
    pq.push(a);
  }
  double res = 0.0;
  while (pq.size() > 1) {
    auto a1 = pq.top();
    pq.pop();
    a1 += pq.top();
    pq.pop();
    res += a1 * 0.05;
    pq.push(a1);
  }
  out << fixed << setprecision(2) << res;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{"4 10 11 12 13 ", "2 1 1"};
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
