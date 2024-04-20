#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  long p, v, q, m;
  cin >> p >> v >> q >> m;
  long x1 = p - v;
  long y1 = p + v;
  long x2 = q - m;
  long y2 = q + m;

  if (x1 > x2) {
    swap(x1, x2);
    swap(y1, y2);
  }
  if (y1 > y2) {
    cout << y1 - x1 + 1;
  } else if (y1 < x2) {
    cout << y1 - x1 + 1 + y2 - x2 + 1;
  } else {
    cout << y2 - x1 + 1;
  }
}
