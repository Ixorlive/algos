#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

using vi = vector<int>;

struct Edge {
  int from, to, flow;
};
int h, w;
using Graph = vector<vector<Edge>>;
Graph graph;
vector<bool> ch;
int sum = 0, tsum = 0, maxf = 0;

int g(int i, int j) { return i * w + j + 1; }

int val(char a) {
  if (a == 'H')
    return 1;
  if (a == 'O')
    return 2;
  if (a == 'N')
    return 3;
  if (a == 'C')
    return 4;
  return 0;
}

void ae(int from, int to, int flow = 1) {
  graph[from].push_back({from, to, flow});
}

int push_flow(int cur = 0, int cap = 5) {
  ch[cur] = true;
  if (cur == h * w + 1) {
    maxf += cap;
    return cap;
  }
  for (int i = 0; i < graph[cur].size(); ++i) {
    Edge e = graph[cur][i];
    if (ch[e.to] || e.flow == 0)
      continue;
    int min_cap = push_flow(e.to, min(e.flow, cap));
    if (min_cap > 0) {
      graph[cur][i].flow -= min_cap;
      int child = -1;
      for (int j = 0; j < graph[e.to].size(); ++j) {
        if (graph[e.to][j].to == e.from) {
          child = j;
          break;
        }
      }
      if (child != -1)
        graph[e.to][child].flow += min_cap;
      else
        graph[e.to].push_back({e.to, cur, min_cap});
      return min_cap;
    }
  }
  return 0;
}

void solve(std::istream &in, std::ostream &out) {
  in >> h >> w;
  auto nv = h * w + 2;
  graph.resize(nv);
  ch.resize(nv, false);
  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      char a;
      in >> a;
      if ((i + j) % 2 == 0) {
        ae(0, g(i, j), val(a));
        sum += val(a);
        if (i + 1 < h)
          ae(g(i, j), g(i + 1, j));
        if (j + 1 < w)
          ae(g(i, j), g(i, j + 1));
        if (i - 1 >= 0)
          ae(g(i, j), g(i - 1, j));
        if (j - 1 >= 0)
          ae(g(i, j), g(i, j - 1));
      } else {
        ae(g(i, j), nv - 1, val(a));
        tsum += val(a);
      }
    }
  }
  while (push_flow()) {
    std::fill(ch.begin(), ch.end(), false);
  }
  bool res = (maxf == sum) && (maxf == tsum) && (maxf != 0);
  out << (res ? "Valid" : "Invalid");
}

void Test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  solve(std::cin, std::cout);
}

void Test() {
  vector<string> inputs = {string("3 4\n"
                                  "HOH.\n"
                                  "NCOH\n"
                                  "OO.."),
                           string("3 4\n"
                                  "HOH.\n"
                                  "NCOH\n"
                                  "OONH")};
  auto outputs = {0};
  for (auto &input : inputs) {
    std::istringstream in(input);
    std::ostringstream out;
    solve(in, out);
    std::cout << out.str();
  }
};
