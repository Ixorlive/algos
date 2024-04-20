#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int heap[100000 + 100];
size_t len = 0;

void swiftup(int i) {
  int p = (i - 1) / 2;
  while (i && heap[p] < heap[i]) {
    swap(heap[p], heap[i]);
    i = p;
    p = (p - 1) / 2;
  }
}

void swiftdown(int i) {
  while (2 * i + 1 < len) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int j = l;
    if (r < len && heap[r] > heap[l])
      j = r;
    if (heap[i] >= heap[j])
      break;
    swap(heap[i], heap[j]);
    i = j;
  }
}

void insert(int val) {
  heap[len] = val;
  ++len;
  swiftup(len - 1);
}

int extract() {
  if (len == 0)
    return 0;
  int mmax = heap[0];
  heap[0] = heap[len - 1];
  --len;
  swiftdown(0);
  return mmax;
}

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  int q, val;
  for (size_t i = 0; i < n; i++) {
    in >> q;
    if (q == 0) {
      in >> val;
      insert(val);
    } else {
      out << extract() << '\n';
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
  vector<string> inputs{
      "14 0 1 0 345 1 0 4346 1 0 2435 1 0 235 0 5 0 365 1 1 1 1 "};
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
