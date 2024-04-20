#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

char pic[201][201];

void solve(istream &in, std::ostream &out) {
  int n, m;
  in >> n >> m;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      in >> pic[i][j];
    }
  }
  int c = 0;
  int x1, x2, y1, y2;
  int tx, ty;
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      if (pic[i][j] == '#') {
        ++c;
        if (c == 3) {
          out << "NO";
          return;
        }
        x1 = i;
        y1 = j;
        y2 = j;
        for (; y2 + 1 < m && pic[i][y2 + 1] == '#'; ++y2) {
        }
        x2 = x1;
        int k = j;
        while (x2 + 1 < n && pic[x2 + 1][y1] == '#') {
          if (y1 > 0 && pic[x2 + 1][y1 - 1] == '#' && y1 != m - 1)
            break;
          ++x2;
          for (int l = y1 + 1; l <= y2; l++) {
            if (pic[x2][l] != '#') {
              y2 = l - 1;
            }
          }
        }
        for (size_t x = x1; x <= x2; x++) {
          for (size_t y = y1; y <= y2; y++) {
            pic[x][y] = c == 1 ? 'a' : 'b';
          }
        }
        if (c == 1) {
          tx = x1;
          ty = y1;
        }
      }
    }
  }
  if (c == 0) {
    out << "NO";
    return;
  }
  if (c == 1) {
    if (ty + 1 < m && pic[tx][ty + 1] == 'a') {
      for (; tx < n && pic[tx][ty] == 'a'; ++tx) {
        pic[tx][ty] = 'b';
      }
    } else if (tx + 1 < n && pic[tx + 1][ty] == 'a') {
      pic[tx][ty] = 'b';
    } else {
      out << "NO";
      return;
    }
  }
  out << "YES\n";
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      out << pic[i][j];
    }
    out << '\n';
  }
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{" 2 1 # . ",         "2 2 .. ## ", "1 3 ### ",
                        "1 5 ####. ",        "3 1 .##",    "2 4 .#..###.",
                        "3 4 ...# #### ...#"};
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
