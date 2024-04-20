#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  char board[8 * 8];
  for (size_t i = 0; i < 8 * 8; i++) {
    in >> board[i];
  }
  int res = 0;
  auto get_i = [](int x, int y) { return x * 8 + y; };
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (board[get_i(i, j)] != '*') {
        continue;
      }
      bool f = false;
      // vert left
      for (int k = j - 1; k >= 0; --k) {
        if (board[get_i(i, k)] == 'R')
          f = true;
        if (board[get_i(i, k)] == 'B')
          break;
      }
      // vert right
      for (int k = j + 1; k < 8; ++k) {
        if (board[i * 8 + k] == 'R')
          f = true;
        if (board[i * 8 + k] == 'B')
          break;
      }
      // horiz up
      for (int k = i - 1; k >= 0; --k) {
        if (board[k * 8 + j] == 'R')
          f = true;
        if (board[k * 8 + j] == 'B')
          break;
      }
      // horiz down
      for (int k = i + 1; k < 8; k++) {
        if (board[k * 8 + j] == 'R')
          f = true;
        if (board[k * 8 + j] == 'B')
          break;
      }
      if (f) {
        continue;
      }
      // B
      for (int k = 0; i - k >= 0 && j - k >= 0; ++k) {
        if (board[get_i(i - k, j - k)] == 'B')
          f = true;
        if (board[get_i(i - k, j - k)] == 'R')
          break;
      }
      for (int k = 0; i + k < 8 && j - k >= 0; ++k) {
        if (board[get_i(i + k, j - k)] == 'B')
          f = true;
        if (board[get_i(i + k, j - k)] == 'R')
          break;
      }
      for (int k = 0; i - k >= 0 && j + k < 8; ++k) {
        if (board[get_i(i - k, j + k)] == 'B')
          f = true;
        if (board[get_i(i - k, j + k)] == 'R')
          break;
      }
      for (int k = 0; i + k < 8 && j + k < 8; ++k) {
        if (board[get_i(i + k, j + k)] == 'B')
          f = true;
        if (board[get_i(i + k, j + k)] == 'R')
          break;
      }
      if (!f)
        ++res;
    }
  }
  out << res;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"*RB***** ******** *R****** ******** ******** ******** "
                        "******** ********"};
  for (int i = 0; i < inputs.size(); ++i) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
