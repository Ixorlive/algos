#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vb = vector<bool>;

const ll MAX = 1e9;

struct Edge {
  ll c, f;
  int u, v, rev;
};
using ve = vector<Edge>;

struct Graph {
  vvi adj;
  ve ed;
  int sink, source;
};

void add_edge(Graph &g, int from, int to, int cap = 1) {
  g.adj[from].push_back(g.ed.size());
  g.ed.push_back({cap, 0, from, to, (int)g.ed.size() + 1});
  g.adj[to].push_back(g.ed.size());
  g.ed.push_back({0, 0, to, from, (int)g.ed.size() - 1});
}

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

constexpr int kM = 1001;
constexpr int kN = 200 + 10;
int costs[kN]{0};
bool vis[kN]{0};

ll get(Graph &G, int u) {
  int res = 0;
  res += costs[u];
  vis[u] = 1;
  for (auto idx : G.adj[u]) {
    Edge &e = G.ed[idx];
    if (!vis[e.v] && (G.ed[idx].c - G.ed[idx].f) != 0) {
      res += get(G, e.v);
    }
  }
  return res;
}

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  Graph g{vvi(n + 2), {}, 1, 0};
  costs[0] = 0;
  costs[1] = 0;
  for (size_t i = 0; i < n; i++) {
    in >> costs[i + 2];
    add_edge(g, 0, i + 2, kM + costs[i + 2]);
    add_edge(g, i + 2, 1, kM);
  }
  int k, v;
  for (size_t i = 0; i < n; i++) {
    in >> k;
    for (size_t j = 0; j < k; j++) {
      in >> v;
      add_edge(g, i + 2, v + 1, 1e6);
    }
  }
  maxflow(g);
  out << get(g, 0);
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"4 -1 1 -2 2 0 1 1 2 4 2 1 1"};
  for (int i = 0; i < inputs.size(); ++i) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
