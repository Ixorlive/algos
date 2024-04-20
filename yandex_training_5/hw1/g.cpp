#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int ch(int a, int b) {
  if (a > b)
    return 1;
  int res = 0;
  while (a > 0 && b > 0) {
    b -= a;
    a -= b;
    ++res;
  }
  if (a > 0) {
    return res;
  }
  return 0;
}

void solve(istream &in, std::ostream &out) {
  int x, y, p;
  in >> x >> y >> p;
  int round = 1;
  int cur_sold = p;
  y -= x;
  if (y <= 0) {
    out << 1;
    return;
  }
  while ((y > 0 || cur_sold > 0) && x > 0) {
    ++round;
    if (y <= 0) {
      auto r = ch(x, cur_sold);
      if (r > 0) {
        round += r - 1;
      } else {
        x = -1;
      }
      break;
    }
    if (x > y) {
      auto q = 2 * x - cur_sold - y;
      auto w = cur_sold - x + y;
      auto r = ch(q, w);
      if (r) {
        if (r > 1) {
          int t_c = cur_sold;
          int t_x = x;
          int t_y = y;
          t_y -= x - cur_sold;
          t_c = p;
          auto t_q = 2 * x - t_c - t_y;
          auto t_w = t_c - x + t_y;
          auto t_r = ch(t_q, t_w);
          if (t_r > 0 && abs(r - t_r) > 1) {
            y = t_y;
            cur_sold = t_c;
            continue;
          }
        }
        // cout << "=== " << y << " ===";
        x = q;
        cur_sold = w;
        y = 0;
        continue;
      } else {
        if (cur_sold >= x) {
          x = -1;
          break;
        }
        y -= x - cur_sold;
        cur_sold = 0;
      }
    } else {
      if (cur_sold >= x) {
        x = -1;
        break;
      }
      y -= x - cur_sold;
      cur_sold = 0;
    }
    cur_sold += p;
  }

  out << (x > 0 ? round : -1);
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"10 11 15",  "1 2 1",       "1 1 1",
                        "25 200 10", "250 500 249", "250 500 218"};
  int i = 5;
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
