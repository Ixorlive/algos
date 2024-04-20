#include <cstdint>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

typedef uint64_t ui64;
typedef int64_t i64;
typedef uint32_t ui32;
typedef int32_t i32;
typedef uint16_t ui16;
typedef int16_t i16;
typedef uint8_t ui8;
typedef int8_t i8;
using namespace std;

using vi = vector<int>;
int n, m;
const int MAX = 4005;
int graph[MAX][MAX];
int match[MAX]{0};
int match2[MAX]{0};
int vis[MAX]{0};
int vis2[MAX]{0};

void dfs(int u) {
  vis[u] = 1;
  for (int v = 1; v <= n; ++v) {
    if (graph[u][v] && !vis2[v] && match[u] != v) {
      vis2[v] = 1;
      if (match2[v] && !vis[match2[v]])
        dfs(match2[v]);
    }
  }
}

void solve(std::istream &in, std::ostream &out) {
  in >> m >> n;
  for (int v = 1; v <= m; ++v) {
    int ki;
    in >> ki;
    for (int i = 0; i < ki; ++i) {
      int u;
      in >> u;
      graph[v][u] = 1;
    }
  }
  for (int i = 1; i <= m; ++i) {
    int u;
    in >> u;
    if (u) {
      match[i] = u;
      match2[u] = i;
    }
  }
  for (int u = 1; u <= m; ++u) {
    if (!match[u] && !vis[u]) {
      dfs(u);
    }
  }

  vi left;
  vi right;
  left.reserve(m);
  right.reserve(n);
  for (int i = 1; i <= m; ++i) {
    if (!vis[i])
      left.push_back(i);
  }
  for (int i = 1; i <= n; ++i) {
    if (vis2[i])
      right.push_back(i);
  }
  out << left.size() + right.size() << '\n';
  out << left.size() << ' ';
  std::copy(left.begin(), left.end(), ostream_iterator<int>(out, " "));
  out << '\n' << right.size() << ' ';
  std::copy(right.begin(), right.end(), ostream_iterator<int>(out, " "));
}

void Test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  solve(std::cin, std::cout);
}

void Test() {
  vector<string> inputs = {string("3 2\n"
                                  "2 1 2\n"
                                  "1 2\n"
                                  "1 2\n"
                                  "1 2 0"),
                           string("1 1\n"
                                  "1 1\n"
                                  "1")};
  auto outputs = {0};
  for (auto &input : inputs) {
    std::istringstream in(input);
    std::ostringstream out;
    solve(in, out);
    std::cout << out.str();
  }
};
