#include <climits>
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;

const int MAXN = 50000, MAXLOG = 16;

constexpr int log2(int n) {
  int res = 0;
  while (n) {
    n >>= 1;
    res++;
  }
  return res;
}

int n, depth[MAXN + 1], parent[MAXN + 1][MAXLOG], min_edge[MAXN + 1][MAXLOG];

int lca(int u, int v, int log_n) {
  if (depth[u] < depth[v])
    swap(u, v);
  log_n -= 1;
  for (int i = log_n; i >= 0; i--) {
    if (depth[parent[u][i]] >= depth[v]) {
      u = parent[u][i];
    }
  }
  if (u == v)
    return u;
  for (int i = log_n; i >= 0; i--) {
    if (parent[u][i] != parent[v][i]) {
      u = parent[u][i];
      v = parent[v][i];
    }
  }
  return parent[v][0];
}

int query(int u, int v, int log_n) {
  int w = lca(u, v, log_n);
  int min_edge_uv = INT_MAX;
  log_n -= 1;
  for (int i = log_n; i >= 0; --i) {
    if (depth[parent[u][i]] >= depth[w]) {
      min_edge_uv = min(min_edge_uv, min_edge[u][i]);
      u = parent[u][i];
    }
  }
  for (int i = log_n; i >= 0; --i) {
    if (depth[parent[v][i]] >= depth[w]) {
      min_edge_uv = min(min_edge_uv, min_edge[v][i]);
      v = parent[v][i];
    }
  }
  return min_edge_uv;
}

void CheapestEdge(std::istream &in, std::ostream &out) {
  in >> n;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j < MAXLOG; ++j) {
      min_edge[i][j] = INT_MAX;
    }
  }
  for (int i = 1; i < n; i++) {
    in >> parent[i][0] >> min_edge[i][0];
    parent[i][0]--;
    depth[i] = depth[parent[i][0]] + 1;
  }
  auto log_n = log2(n);
  for (int i = 1; i < log_n; ++i) {
    for (int j = 1; j < n; ++j) {
      parent[j][i] = parent[parent[j][i - 1]][i - 1];
      min_edge[j][i] =
          min(min_edge[j][i - 1], min_edge[parent[j][i - 1]][i - 1]);
    }
  }

  int m;
  in >> m;
  while (m--) {
    int u, v;
    in >> u >> v;
    --u;
    --v;
    out << query(u, v, log_n) << "\n";
  }
}

void Test(){{std::istringstream in{"5\n"
                                   "1 2\n"
                                   "1 3\n"
                                   "2 5\n"
                                   "3 2\n"
                                   "2\n"
                                   "2 3\n"
                                   "4 5"};
std::ostringstream out;
CheapestEdge(in, out);
cout << out.str();
//    assert(out.str() == "");
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //  Test();
  CheapestEdge(std::cin, std::cout);
  return 0;
}
