#include <algorithm>
#include <bitset>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// vector<bool> tests = {1,1,1,1};
// vector<bool> tests = {0,0,0,0};
vector<bool> tests = {0, 0, 1, 0};
// vector<bool> tests = {1, 0,0,0};

void Test();

constexpr int kM = 2000;
bitset<kM> a[kM];
bitset<kM> b[kM];
bitset<kM> s;
bitset<kM> r;
int n, m;

void gauss() {
  int rw = 0;
  for (int col = 0; rw < m && col < n; ++col) {
    if (!a[rw][col]) {
      for (int i = rw + 1; i < m; ++i) {
        if (a[i][col]) {
          swap(a[rw], a[i]);
          break;
        }
      }
    }
    if (!a[rw][col])
      continue;
    for (int i = rw + 1; i < m; ++i) {
      if (a[i][col]) {
        a[i] ^= a[rw];
      }
    }
    ++rw;
  }
  for (int row = m - 1; row >= 0; --row) {
    int pivot(-1);
    for (int col = 0; col < n - 1; ++col) {
      if (a[row][col]) {
        pivot = col;
        break;
      }
    }
    if (pivot == -1) {
      continue;
    } else {
      r[pivot] = a[row][n - 1];
      for (int col = pivot + 1; col < n - 1; ++col) {
        r[pivot] = (r[pivot] != (a[row][col] & r[col]));
      }
    }
  }
}

void solve(istream &in, ostream &out) {
  in >> n >> m;
  // r.reset();
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      bool v;
      in >> v;
      a[i][j] = v;
      b[j][i] = v;
    }
  }
  for (int col = 0; col < n; ++col) {
    int row = 0;
    while (row < m && (!a[row][col] || s[row])) {
      ++row;
    }
    if (row == m)
      continue;
    s[row] = true;
    for (int i = row + 1; i < m; ++i) {
      if (a[i][col])
        a[i] ^= a[row];
    }
  }
  for (int i = 0; i < m; ++i) {
    if (s[i])
      out << "No\n";
    else
      out << "Yes\n";
  }
  if (!s[m - 1]) {
    swap(a, b);
    swap(n, m);
    gauss();
    for (int i = 0; i < n - 1; ++i) {
      if (r[i])
        out << "1 ";
      else
        out << "0 ";
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  //    Test();
  solve(std::cin, std::cout);
  return 0;
}

void Test() {
  int ind = 0;
  {
    if (tests[ind++]) {
      std::istringstream in{"4 6\n"
                            "0 0 0 0\n"
                            "1 0 0 1\n"
                            "1 0 1 0\n"
                            "0 0 1 1\n"
                            "0 1 0 0\n"
                            "0 1 1 1"};
      std::ostringstream out;
      solve(in, out);
      //            cout << out.str();
      assert(out.str() == "Yes\n"
                          "No\n"
                          "No\n"
                          "Yes\n"
                          "No\n"
                          "Yes\n"
                          "0 1 1 0 1 ");
    }
  }
  {
    if (tests[ind++]) {
      std::istringstream in{"1 1\n"
                            "1"};
      std::ostringstream out;
      solve(in, out);
      //            cout << out.str();
      assert(out.str() == "No\n");
    }
  }
  {
    if (tests[ind++]) {
      std::istringstream in{"4 5\n"
                            "1 0 0 0\n"
                            "0 1 1 0\n"
                            "0 1 0 0\n"
                            "0 0 1 1\n"
                            "1 1 0 0"};
      std::ostringstream out;
      solve(in, out);
      //            cout << out.str();
      assert(out.str() == "No\n"
                          "No\n"
                          "No\n"
                          "No\n"
                          "Yes\n"
                          "1 0 1 0 ");
    }
  }
  {
    if (tests[ind++]) {
      std::istringstream in{"4 5\n"
                            "1 0 0 0\n"
                            "0 1 1 0\n"
                            "0 1 0 0\n"
                            "0 0 1 1\n"
                            "1 1 1 1"};
      std::ostringstream out;
      solve(in, out);
      //            cout << out.str();
      assert(out.str() == "No\n"
                          "No\n"
                          "No\n"
                          "No\n"
                          "Yes\n"
                          "1 0 1 1 ");
    }
  }
};
