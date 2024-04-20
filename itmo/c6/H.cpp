#include <cmath>
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

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  int pair_count = ((n - 1) * (n - 2)) / 2;
  Graph g{vvi(n + 1 + pair_count), {}, 1, 0};
  vi teams_wins(n);
  for (size_t i = 0; i < n; i++) {
    in >> teams_wins[i];
  }
  vi total_games(n);
  for (size_t i = 0; i < n; i++) {
    in >> total_games[i];
  }
  int max_wins = teams_wins[0] + total_games[0];
  int skip;
  for (size_t i = 0; i < n; i++) {
    in >> skip;
  }
  int ind = n + 1;
  int matches;
  int nGames = 0;
  for (size_t i = 1; i < n; i++) {
    if (teams_wins[i] > max_wins) {
      out << "NO";
      return;
    }
    total_games[i] = 0;
    for (size_t j = 0; j <= i; j++) {
      in >> skip;
      total_games[i] += skip;
    }
    for (size_t j = i + 1; j < n; j++) {
      in >> matches;
      total_games[i] += matches;
      nGames += matches;
      add_edge(g, g.source, ind, matches);
      add_edge(g, ind, i + 1, MAX);
      add_edge(g, ind, j + 1, MAX);
      ++ind;
    }
    auto max_wins_for_team = total_games[i];
    if (teams_wins[i] + max_wins_for_team > max_wins) {
      max_wins_for_team = max_wins - teams_wins[i];
    }
    add_edge(g, i + 1, g.sink, max_wins_for_team);
  }
  if (maxflow(g) == nGames) {
    out << "YES";
  } else {
    out << "NO";
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
