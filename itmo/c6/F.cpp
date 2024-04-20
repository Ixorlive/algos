#include <cstring>
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

int n, m;

int get_in(int i, int j) { return i * m + j; }

int get_out(int i, int j) { return i * m + j + n * m; }

void add_edge_helper(Graph &g, int i1, int j1, int i2, int j2) {
  add_edge(g, get_out(i1, j1), get_in(i2, j2), MAX);
  add_edge(g, get_out(i2, j2), get_in(i1, j1), MAX);
}

void dfs_reachables(Graph &g, int u, vi &vis, vi &reachable) {
  vis[u] = true;
  reachable.push_back(u);
  for (const auto &idx : g.adj[u]) {
    Edge &ed = g.ed[idx];
    if (!vis[ed.v] && ed.f < ed.c) {
      dfs_reachables(g, ed.v, vis, reachable);
    }
  }
}

void solve(istream &in, std::ostream &out) {
  in >> n >> m;
  size_t n_vertexs = n * m * 2;
  int k, l;
  in >> k >> l;
  int x, y;
  Graph g{vvi(n_vertexs), {}, 0, 0};
  vector<vector<bool>> vis(n, vector<bool>(m, false));
  for (size_t i = 0; i < k; i++) {
    in >> x >> y;
    --x, --y;
    vis[x][y] = true;
    add_edge(g, get_in(x, y), get_out(x, y), 0);
  }
  for (size_t i = 0; i < l; i++) {
    in >> x >> y;
    --x, --y;
    vis[x][y] = true;
    add_edge(g, get_in(x, y), get_out(x, y), 1);
  }
  in >> x >> y;
  --x, --y;
  vis[x][y] = true;
  g.source = get_out(x, y);
  in >> x >> y;
  --x, --y;
  vis[x][y] = true;
  g.sink = get_in(x, y);
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < m; j++) {
      if (!vis[i][j]) {
        vis[i][j] = true;
        add_edge(g, get_in(i, j), get_out(i, j), MAX);
      }
      if (i < n - 1) {
        add_edge_helper(g, i, j, i + 1, j);
      }
      if (j < m - 1) {
        add_edge_helper(g, i, j, i, j + 1);
      }
    }
  }
  int mf = maxflow(g);
  if (mf >= MAX) {
    out << "-1";
  } else {
    vi reachable;
    reachable.reserve(n_vertexs);
    vi vis(n_vertexs, 0);
    dfs_reachables(g, g.source, vis, reachable);
    vi ans;
    ans.reserve(n_vertexs);
    for (int u : reachable) {
      for (const auto idx : g.adj[u]) {
        Edge &e = g.ed[idx];
        if (!vis[e.v] && e.f == 1) {
          ans.push_back(e.v);
        }
      }
    }
    out << ans.size() << '\n';
    for (auto v : ans) {
      v -= n * m;
      out << v / m + 1 << " " << v % m + 1 << '\n';
    }
  }
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{};
  for (int i = 0; i < inputs.size(); ++i) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
