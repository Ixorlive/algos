#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <queue>
#include <sstream>
#include <unordered_map>
#include <vector>

void IslandCountry(std::istream &in, std::ostream &out) {
  using Vertex = size_t;
  using Graph = std::vector<std::vector<Vertex>>;
  size_t n, m;
  in >> n >> m;
  Graph g(n, std::vector<Vertex>());
  std::vector<size_t> v_to_state(n);
  for (int i = 0; i < n; ++i) {
    in >> v_to_state[i];
  }
  for (int i = 0; i < m; ++i) {
    size_t from, to;
    in >> from >> to;
    --from;
    --to;
    g[from].push_back(to);
    g[to].push_back(from);
  }
  std::vector<std::queue<Vertex>> qs(3);
  size_t i = 0;
  auto v_finish = n - 1;
  qs[i].push(0);
  std::vector<int> visited(n, -1);
  std::unordered_map<size_t, Vertex> back_path;
  size_t cost = 0;
  size_t min_cost = 1 << 24;
  auto get_weight = [&](Vertex from, Vertex to) {
    return (int)(v_to_state[from] != v_to_state[to]) *
           ((int)((from + 1) % 2 == 0) + 1);
  };
  while (true) {
    Vertex cur_v;
    do {
      if (qs[0].empty() && qs[1].empty() && qs[2].empty()) {
        out << "impossible";
        return;
      }
      while (qs[i].empty()) {
        i = (i + 1) % 3;
        ++cost;
      }
      cur_v = qs[i].front();
      if (cur_v == v_finish)
        break;
      qs[i].pop();
    } while (visited[cur_v] == 3);
    if (cur_v == v_finish)
      break;
    for (const auto &adj_v : g[cur_v]) {
      auto w = get_weight(cur_v, adj_v);
      if (visited[adj_v] != 3 &&
          (visited[adj_v] == -1 || (visited[adj_v] > w))) {
        visited[adj_v] = w;
        if (adj_v == v_finish) {
          if (w + cost < min_cost) {
            back_path[adj_v] = cur_v;
            min_cost = w + cost;
          }
        } else {
          back_path[adj_v] = cur_v;
        }
        qs[(i + w) % 3].push(adj_v);
      }
    }
    visited[cur_v] = 3;
  }
  std::vector<Vertex> res;
  res.reserve(64);
  while (true) {
    res.push_back(v_finish + 1);
    if (v_finish == 0) {
      out << cost << " " << res.size() << '\n';
      std::copy(res.rbegin(), res.rend(),
                std::ostream_iterator<Vertex>(out, " "));
      return;
    }
    v_finish = back_path[v_finish];
  }
}

void Test() {
  {
    std::istringstream in("7 8\n"
                          "1 1 1 1 2 2 1\n"
                          "1 2\n"
                          "2 5\n"
                          "2 3\n"
                          "5 4\n"
                          "4 3\n"
                          "4 7\n"
                          "1 6\n"
                          "6 7");
    std::ostringstream out;
    IslandCountry(in, out);
    //        std::cout << out.str();
    assert(out.str() == "0 5\n"
                        "1 2 3 4 7 ");
  }
  {
    std::istringstream in("5 5\n"
                          "1 2 1 1 2\n"
                          "1 2\n"
                          "2 3\n"
                          "3 5\n"
                          "1 4\n"
                          "4 5");
    std::ostringstream out;
    IslandCountry(in, out);
    assert(out.str() == "2 3\n"
                        "1 4 5 ");
  }
  {
    std::istringstream in("2 1\n"
                          "1 2\n"
                          "1 2");
    std::ostringstream out;
    IslandCountry(in, out);
    assert(out.str() == "1 2\n"
                        "1 2 ");
  }
  {
    std::istringstream in("5 3\n"
                          "1 1 1 1 1\n"
                          "1 2\n"
                          "2 3\n"
                          "4 5");
    std::ostringstream out;
    IslandCountry(in, out);
    //        std::cout << out.str();
    assert(out.str() == "impossible");
  }
  {
    std::istringstream in("6 7\n"
                          "1 1 1 1 1 2\n"
                          "1 2\n"
                          "2 6\n"
                          "1 3\n"
                          "3 4\n"
                          "4 5\n"
                          "5 6");
    std::ostringstream out;
    IslandCountry(in, out);
    std::cout << out.str();
    //        assert(out.str() == "impossible");
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //    Test();
  IslandCountry(std::cin, std::cout);
}
