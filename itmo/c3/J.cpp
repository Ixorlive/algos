#include <cassert>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

struct Edge {
  int from{};
  int to{};
  int weight{};
};

using Graph = std::vector<std::vector<int>>;

void bfs(const Graph &g, int from_v, std::vector<bool> &visited) {
  visited[from_v] = true;
  for (const auto &adj_v : g[from_v]) {
    if (!visited[adj_v])
      bfs(g, adj_v, visited);
  }
}

void BellmanFord(std::istream &in, std::ostream &out) {
  int n, m;
  in >> n >> m;
  std::vector<Edge> edges(m);
  Graph g(n);
  for (int i = 0; i < m; ++i) {
    Edge e;
    in >> e.from >> e.to >> e.weight;
    --e.from;
    --e.to;
    edges[i] = e;
    g[e.to].push_back(e.from);
  }
  std::vector<int> dist(n, INT32_MIN);
  std::vector<int> prev(n, -1);
  dist[0] = 0;
  for (int i = 0; i < n; ++i) {
    for (const Edge &e : edges) {
      if ((dist[e.from] > INT32_MIN) &&
          (dist[e.to] < dist[e.from] + e.weight)) {
        dist[e.to] = dist[e.from] + e.weight;
        prev[e.to] = e.from;
      }
    }
  }
  if (dist[n - 1] == INT32_MIN) {
    out << ":(";
    return;
  }
  std::vector<bool> visited(n, false);
  std::vector<bool> b(n, false);
  bfs(g, n - 1, visited);
  int updated_v = 1;
  while (true) {
    updated_v = -1;
    for (const Edge &e : edges) {
      if (!b[e.from] && !b[e.to]) {
        if ((dist[e.from] > INT32_MIN) &&
            (dist[e.to] < dist[e.from] + e.weight)) {
          dist[e.to] = dist[e.from] + e.weight;
          prev[e.to] = e.from;
          updated_v = e.from;
        }
      }
    }
    if (updated_v == -1) {
      break;
    }
    std::vector<int> c;
    c.reserve(n);
    int prev_v = updated_v;
    for (int i = 0; i < n; ++i) {
      prev_v = prev[prev_v];
    }
    for (int i = prev_v;; i = prev[i]) {
      c.push_back(i);
      if (i == prev_v && c.size() > 1) {
        break;
      }
    }
    for (const auto v : c) {
      b[v] = true;
    }
  }
  for (int i = 0; i < n; ++i) {
    if (visited[i] && b[i]) {
      out << ":)";
      return;
    }
  }
  out << dist.back();
}

void Test(){{std::istringstream in("2 2\n"
                                   "1 2 5\n"
                                   "1 2 -10");
std::ostringstream out;
BellmanFord(in, out);
//        std::cout << out.str();
assert(out.str() == "5");
}
{
  std::istringstream in("2 2\n"
                        "1 2 3\n"
                        "2 1 7");
  std::ostringstream out;
  BellmanFord(in, out);
  //        std::cout << out.str();
  assert(out.str() == ":)");
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //    Test();
  BellmanFord(std::cin, std::cout);
}
