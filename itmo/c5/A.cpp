#include <iostream>
#include <numeric>
#include <sstream>

using namespace std;
constexpr int MAX_N = 200;
bool A[MAX_N][MAX_N];
bool B[MAX_N][MAX_N];
bool c[MAX_N];
bool c2[MAX_N];
bool r[MAX_N]{false};
int N = 1;

bool solve() {
  for (int row = 0, col = 0; row < N && col < N; ++col) {
    int pivot = row;
    if (!A[row][col]) {
      for (int i = row + 1; i < N; ++i) {
        if (A[i][col]) {
          pivot = i;
          break;
        }
      }
      swap(A[pivot], A[row]);
      swap(c[pivot], c[row]);
    }
    if (!A[row][col])
      continue;
    for (int i = row + 1; i < N; ++i) {
      if (A[i][col]) {
        for (int j = col; j < N; ++j) {
          A[i][j] ^= A[row][j];
        }
        c[i] ^= c[row];
      }
    }
    ++row;
  }
  for (int row = N - 1; row >= 0; --row) {
    int pivot(-1);
    for (int col = 0; col < N; ++col) {
      if (A[row][col]) {
        pivot = col;
        break;
      }
    }
    if (pivot == -1) {
      if (c[row])
        return false;
    } else {
      r[pivot] = c[row];
      for (int col = pivot + 1; col < N; ++col) {
        r[pivot] = (r[pivot] != (A[row][col] & r[col]));
      }
    }
  }
  return true;
}

void MindBrain(std::istream &in, std::ostream &out) {
  in >> N;
  for (int i = 0; i < N; ++i) {
    int k;
    in >> k;
    for (int j = 0; j < k; ++j) {
      int adj_c;
      in >> adj_c;
      A[--adj_c][i] = true;
      B[adj_c][i] = true;
    }
  }
  for (int i = 0; i < N; ++i) {
    in >> c[i];
    c2[i] = !c[i];
  }
  bool solution_found = solve();
  if (!solution_found) {
    swap(A, B);
    swap(c2, c);
    fill(r, r + N, false);
    solution_found = solve();
    if (!solution_found) {
      out << -1 << '\n';
      return;
    }
  }
  int sum = std::accumulate(r, r + N, 0);
  out << sum << ' ';
  for (int i = 0; i < N; ++i) {
    if (r[i])
      out << i + 1 << ' ';
  }
}

void Test(){{std::istringstream in{"9\n"
                                   "3 1 2 4\n"
                                   "4 1 2 3 5\n"
                                   "3 2 3 6\n"
                                   "4 1 4 5 7\n"
                                   "5 2 4 5 6 8\n"
                                   "4 3 5 6 9\n"
                                   "3 4 7 8\n"
                                   "4 5 7 8 9\n"
                                   "3 6 8 9\n"
                                   "1 0 1 0 1 0 1 0 1"};
std::ostringstream out;
//    MindBrain(in, out);
//    cout << out.str();
//    assert(out.str() == "4");
}
{
  std::istringstream in{"6\n"
                        "3 1 2 6\n"
                        "3 2 5 6\n"
                        "4 1 2 3 6\n"
                        "3 3 4 6\n"
                        "3 3 5 6\n"
                        "2 3 4\n"
                        "0 1 0 0 0 0"};
  std::ostringstream out;
  MindBrain(in, out);
  cout << out.str();
  //    assert(out.str() == "4");
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //  Test();
  MindBrain(std::cin, std::cout);
  return 0;
}
