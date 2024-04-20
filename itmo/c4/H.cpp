#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

typedef uint64_t ui64;
typedef int64_t i64;
typedef uint32_t ui32;
typedef int32_t i32;
typedef uint16_t ui16;
typedef int16_t i16;
typedef uint8_t ui8;
typedef int8_t i8;

struct Node {
  ui64 v;
  ui64 weight;
  Node *next;
};

vector<Node> edges;
vector<Node> edges2;
vector<Node *> l;
vector<Node *> l2;
vector<ui64> visited;
vector<ui64> dis;
vector<vector<ui64>> q_v;
vector<ui64> fat;

void add_edge(ui64 v, ui64 u, ui64 w, vector<Node> &e, vector<Node *> &list,
              ui64 &idx) {
  e[idx].v = u;
  e[idx].weight = w;
  e[idx].next = list[v];
  list[v] = e.data() + idx++;
  e[idx].v = v;
  e[idx].weight = w;
  e[idx].next = list[u];
  list[u] = e.data() + idx++;
}

ui64 find(ui64 v) {
  if (v != fat[v])
    return fat[v] = find(fat[v]);
  return v;
}

void build(ui64 v) {
  visited[v] = 1;
  fat[v] = v;
  for (auto n = l2[v]; n; n = n->next) {
    if (visited[n->v]) {
      q_v[n->weight][2] = find(n->v);
    }
  }
  for (auto n = l[v]; n; n = n->next) {
    if (!visited[n->v]) {
      dis[n->v] = dis[v] + n->weight;
      build(n->v);
      fat[n->v] = v;
    }
  }
}

void Tree(std::istream &in, std::ostream &out) {
  ui64 n, m;
  in >> n;
  edges.resize(2 * n + 1);
  l.resize(n + 1);
  l2.resize(n + 1);
  ui64 idx = 0;
  ui64 v, u, w;
  for (int i = 1; i < n; ++i) {
    in >> v >> u >> w;
    add_edge(v, u, w, edges, l, idx);
  }
  in >> m;
  q_v.resize(m + 1, vector<ui64>(3));
  edges2.resize(4 * m + 1);
  idx = 0;
  for (ui64 i = 1; i <= m; ++i) {
    in >> v >> u;
    add_edge(v, u, i, edges2, l2, idx);
    q_v[i][0] = v;
    q_v[i][1] = u;
  }
  visited.resize(n + 1);
  dis.resize(n + 1);
  fat.resize(n + 1);
  dis[1] = 0;
  build(1);
  for (int i = 1; i <= m; ++i) {
    out << dis[q_v[i][0]] + dis[q_v[i][1]] - 2 * dis[q_v[i][2]] << '\n';
  }
}

void Test(){{std::istringstream in{"3\n"
                                   "1 0 1\n"
                                   "2 0 1\n"
                                   "9\n"
                                   "0 0\n"
                                   "0 1\n"
                                   "0 2\n"
                                   "1 0\n"
                                   "1 1\n"
                                   "1 2\n"
                                   "2 0\n"
                                   "2 1\n"
                                   "2 2"};
std::ostringstream out;
Tree(in, out);
cout << out.str();
//    assert(out.str() == "0\n"
//                        "1\n"
//                        "1\n"
//                        "1\n"
//                        "0\n"
//                        "2\n"
//                        "1\n"
//                        "2\n"
//                        "0");
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //  Test();
  Tree(std::cin, std::cout);
  return 0;
}
