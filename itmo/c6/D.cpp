#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
using ll = long long;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vb = vector<bool>;

const ll MAX = 1e6;
constexpr int kM = 500 + 10;

struct Order {
  int h, m;
  int a, b, c, d;
};

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

Order ords[kM];
int n;

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

void solve(istream &in, std::ostream &out) {
  in >> n;
  char c;
  Graph graph{vvi(2 * n + 2), {}, 1, 0};
  for (size_t i = 0; i < n; i++) {
    in >> ords[i].h >> c >> ords[i].m >> ords[i].a >> ords[i].b >> ords[i].c >>
        ords[i].d;
    add_edge(graph, 0, i + 2);
    add_edge(graph, i + n + 2, 1);
  }
  for (size_t i = 0; i < n; i++) {
    for (size_t j = i + 1; j < n; j++) {
      if (i != j) {
        ll dur = abs(ords[i].a - ords[i].c) + abs(ords[i].b - ords[i].d) +
                 abs(ords[i].c - ords[j].a) + abs(ords[i].d - ords[j].b) + 1;
        int hm = ords[i].m + dur % 60;
        int ha = dur / 60 + ords[i].h + (hm / 60);
        if (ha >= 24)
          continue;
        hm %= 60;
        if (ha < ords[j].h || (ha == ords[j].h && hm <= ords[j].m)) {
          add_edge(graph, i + 2, j + n + 2);
        }
      }
    }
  }
  out << n - maxflow(graph);
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"2\n08:00 10 11 9 16\n08:07 9 16 10 11\n",
                        "2\n08:00 10 11 9 16\n08:06 9 16 10 11\n"};
  for (int i = 0; i < inputs.size(); ++i) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
