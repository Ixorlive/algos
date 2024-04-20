#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vi>;

const ll MAX = 1e5;

struct Edge {
  ll c, f;
  int u, v, rev, id;
};

using ve = vector<Edge>;

struct Graph {
  vvi adj;
  ve ed;
  int sink, source;
};

ll dfs(int node, ll flow, vb &vis, Graph &G) {
  if (node == G.sink)
    return flow;
  vis[node] = true;
  for (auto idx : G.adj[node]) {
    Edge &e = G.ed[idx];
    if (!vis[e.v] && e.f < e.c) {
      ll d = dfs(e.v, min(flow, e.c - e.f), vis, G);
      if (d > 0) {
        G.ed[idx].f += d;
        G.ed[e.rev].f -= d;
        return d;
      }
    }
  }
  return 0;
}

ll maxflow(Graph &G) {
  vb vis(G.adj.size(), false);
  while (dfs(G.source, MAX, vis, G))
    fill(vis.begin(), vis.end(), false);
  ll res = 0;
  for (auto idx : G.adj[G.source])
    res += abs(G.ed[idx].f);
  return res;
}

bool walk(int node, vb &vis, vi &path, const Graph &G) {
  path.push_back(node);
  if (node == G.sink)
    return true;
  for (auto idx : G.adj[node]) {
    if (!vis[idx] && G.ed[idx].f == 1 && idx % 2 == 0) {
      vis[idx] = true;
      if (walk(G.ed[idx].v, vis, path, G))
        return true;
    }
  }
  path.pop_back();
  return false;
}

void solve(istream &in, ostream &out) {
  int n, m, s, t;
  in >> n >> m >> s >> t;
  --s;
  --t;
  Graph G{vvi(n), {}, t, s};
  for (int i = 0; i < m; ++i) {
    int u, v;
    in >> u >> v;
    --u;
    --v;
    G.adj[u].push_back(G.ed.size());
    G.ed.push_back({1, 0, u, v, (int)G.ed.size() + 1, i});
    G.adj[v].push_back(G.ed.size());
    G.ed.push_back({0, 0, v, u, (int)G.ed.size() - 1, i});
  }
  ll mf = maxflow(G);
  if (mf < 2) {
    out << "NO\n";
    return;
  }
  out << "YES\n";
  vb vis(2 * m, false);
  vi path1, path2;
  walk(s, vis, path1, G);
  walk(s, vis, path2, G);
  for (auto u : path1)
    out << u + 1 << ' ';
  for (auto u : path2)
    out << u + 1 << ' ';
  out << '\n';
}

void run_test();

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  // run_test();
  solve(cin, cout);
  return 0;
}

void run_test() {
  vector<string> inputs = {string("3 3 1 3\n"
                                  "1 2\n"
                                  "1 3\n"
                                  "2 3"),
                           string("4 5 1 4\n"
                                  "1 2\n"
                                  "1 3\n"
                                  "2 3\n"
                                  "2 4\n"
                                  "3 4")};
  auto outputs = {0};
  for (auto &input : inputs) {
    std::istringstream in(input);
    std::ostringstream out;
    solve(in, out);
    std::cout << out.str();
  }
};
