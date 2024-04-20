#include <algorithm>
#include <cassert>
#include <iostream>
#include <set>
#include <sstream>
#include <vector>

using namespace std;

using Graph = vector<vector<int>>;

void find_bridge(Graph &g, int from_v, vector<bool> &visited, vector<int> &d,
                 vector<int> &l, vector<int> &p) {
  static int timer = 0;
  visited[from_v] = true;
  d[from_v] = l[from_v] = ++timer;
  for (size_t i = 0; i < g[from_v].size(); ++i) {
    int adj = g[from_v][i];
    if (!visited[adj]) {
      p[adj] = from_v;
      find_bridge(g, adj, visited, d, l, p);
      l[from_v] = min(l[from_v], l[adj]);
      if (l[adj] > d[from_v]) {
        g[from_v][i] = -1;
        auto it = std::find(g[adj].begin(), g[adj].end(), from_v);
        *it = -1;
      }
    } else if (adj != p[from_v]) {
      l[from_v] = min(l[from_v], d[adj]);
    }
  }
}

void dfs(const Graph &g, vector<set<int>> &comp, int from,
         vector<bool> &visited, int n) {
  visited[from] = true;
  comp.back().insert(from);
  for (auto adj : g[from]) {
    if (adj == -1)
      continue;
    if (!visited[adj]) {
      dfs(g, comp, adj, visited, n);
    }
  }
}

void BridgeAndComponents(std::istream &in, std::ostream &out) {
  int n, m;
  in >> n >> m;
  Graph g(n);

  for (int i = 0; i < m; ++i) {
    int from_v, to_v;
    in >> from_v >> to_v;
    --from_v;
    --to_v;
    g[from_v].push_back(to_v);
    g[to_v].push_back(from_v);
  }

  vector<int> d(n);
  vector<int> l(n);
  vector<int> p(n, -1);
  vector<bool> visited(n, false);

  for (int i = 0; i < n; ++i) {
    if (!visited[i])
      find_bridge(g, i, visited, d, l, p);
  }
  int comp = 0;
  std::fill(visited.begin(), visited.end(), false);

  vector<set<int>> components;
  components.reserve(n);
  for (int i = 0; i < n; ++i) {
    if (!visited[i]) {
      components.emplace_back();
      dfs(g, components, i, visited, comp);
    }
  }
  std::sort(components.begin(), components.end());
  out << components.size() << '\n';
  bool t = false;
  for (const auto &component : components) {
    bool first = true;
    if (t) {
      out << '\n';
    }
    t = true;
    for (auto v : component) {
      out << (first ? "" : " ") << (v + 1);
      first = false;
    }
  }
}

void Test(){{std::istringstream in("3 2\n"
                                   "1 2\n"
                                   "2 3");
std::ostringstream out;
BridgeAndComponents(in, out);
//        std::cout << out.str();
assert(out.str() == "3\n"
                    "1\n"
                    "2\n"
                    "3");
}
{
  std::istringstream in("3 3\n"
                        "1 2\n"
                        "2 3\n"
                        "3 1");
  std::ostringstream out;
  BridgeAndComponents(in, out);
  //        std::cout << out.str();
  assert(out.str() == "1\n"
                      "1 2 3");
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //    Test();
  BridgeAndComponents(std::cin, std::cout);
}
