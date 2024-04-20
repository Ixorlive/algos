#include <algorithm>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

constexpr int MAXN = 100 + 10;
int n, m;
int mx[MAXN][MAXN]{0};

struct Move {
  int i, j, fromDi, fromDj;
  Move(int x, int y, int di, int dj) : i(x), j(y), fromDi(di), fromDj(dj) {}
  bool operator==(const Move &m) const {
    return i == m.i && j == m.j && m.fromDi == fromDi && m.fromDj == fromDj;
  }
};

namespace std {
template <> struct hash<Move> {
  size_t operator()(const Move &m) const {
    return m.i * 101 * 101 + m.j * 101 + (m.fromDi + 1) * 3 + (m.fromDj + 1);
  }
};
} // namespace std

const std::vector<std::pair<int, int>> directions = {
    {0, 1}, {1, 0}, {0, -1}, {-1, 0}};

void solve(std::istream &in, std::ostream &out) {
  in >> n >> m;
  for (int i = 0; i <= n + 1; ++i) {
    mx[i][0] = mx[i][m + 1] = 1;
  }
  for (int i = 0; i <= m + 1; ++i) {
    mx[0][i] = mx[n + 1][i] = 1;
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      in >> mx[i][j];
    }
  }

  std::queue<Move> q;
  std::unordered_set<Move> visited;
  q.emplace(1, 1, 0, 0);
  visited.insert(q.front());

  size_t total_movs = 0;
  while (!q.empty()) {
    size_t sz = q.size();
    for (size_t k = 0; k < sz; ++k) {
      Move cur = q.front();
      q.pop();

      for (auto &[di, dj] : directions) {
        if (-di == cur.fromDi && -dj == cur.fromDj)
          continue;

        int ni = cur.i, nj = cur.j;
        while (mx[ni + di][nj + dj] == 0) {
          ni += di;
          nj += dj;
        }

        if (mx[ni + di][nj + dj] == 2) {
          out << total_movs + 1;
          return;
        }

        Move next(ni, nj, di, dj);
        if (visited.insert(next).second) {
          q.push(next);
        }
      }
    }
    ++total_movs;
  }
  // Если выход не найден, выводим, что достигнут конец алгоритма без успеха
  out << "No solution found within the given maze configuration.";
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{" 4 5 0 0 0 0 1 0 1 1 0 2 0 2 1 0 0 0 0 1 0 0 "};
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
