#include <cstdint>
#include <cstring>
#include <iostream>
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
const int MAX = 250;
int n, m;
int g[MAX + 1][MAX + 1], match[MAX + 1], vis[MAX + 1];

bool dfs(int u) {
  for (int v = 1; v <= m; v++) {
    if (g[u][v] && !vis[v]) {
      vis[v] = 1;
      if (!match[v] || dfs(match[v])) {
        match[v] = u;
        return true;
      }
    }
  }
  return false;
}

void solve(std::istream &in, std::ostream &out) {
  in >> n >> m;
  for (int i = 1; i <= n; ++i) {
    int u;
    while (in >> u, u) {
      g[i][u] = 1;
    }
  }
  memset(match, 0, sizeof(match));
  int res = 0;
  for (int i = 1; i <= n; ++i) {
    memset(vis, 0, sizeof(vis));
    res += dfs(i);
  }
  out << res << '\n';
  for (int i = 1; i <= m; ++i) {
    if (match[i]) {
      out << match[i] << " " << i << '\n';
    }
  }
}

void Test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // Test();
  solve(std::cin, std::cout);
}

void Test(){{std::istringstream in("2 2\n"
                                   "1 2 0\n"
                                   "2 0");
std::ostringstream out;
solve(in, out);
std::cout << out.str();
//    assert(out.str() == "20 40 20 0 -1");
}
{
  std::istringstream in("5 5\n"
                        "1 2 3 0\n"
                        "1 4 5 0\n"
                        "1 2 0\n"
                        "3 4 5 0\n"
                        "1 0");
  std::ostringstream out;
  solve(in, out);
  std::cout << out.str();
  //    assert(out.str() == "20 40 20 0 -1");
}
}
;
