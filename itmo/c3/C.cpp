#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <queue>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void KingAssassination(std::istream &in, std::ostream &out) {
  int n, m;
  Graph g;
  std::vector<bool> visited;
  int v_start, v_end;
  in >> n >> m >> v_start >> v_end;
  --v_start;
  --v_end;
  g.resize(n);
  for (int i = 0; i < m; ++i) {
    int from_v, to_v;
    in >> from_v >> to_v;
    --from_v;
    --to_v;
    g[from_v].push_back(to_v);
  }

  visited.resize(n, false);
  std::vector<int> path;
  path.reserve(n);
  std::unordered_map<int, int> v_to_pos;

  std::vector<int> prev(n, -1);
  std::queue<int> vs;
  vs.push(v_start);
  visited[v_start] = true;
  bool found = false;
  // ====================================================================================
  // Find any path from start to end
  // ====================================================================================
  while (!vs.empty()) {
    auto v = vs.front();
    vs.pop();
    for (int adj : g[v]) {
      if (!visited[adj]) {
        if (adj == v_end) {
          prev[adj] = v;
          found = true;
          break;
        }
        visited[adj] = true;
        vs.push(adj);
        prev[adj] = v;
      }
    }
    if (found)
      break;
  }
  int len_path = 0;
  for (int i = v_end; i != -1; i = prev[i]) {
    ++len_path;
  }
  if (len_path <= 2) {
    out << 0;
    return;
  }
  path.resize(len_path);
  auto it = path.rbegin();
  for (int i = v_end; i != -1; i = prev[i]) {
    *it++ = i;
    v_to_pos[i] = --len_path;
  }
  len_path = static_cast<int>(path.size());
  std::stack<int> s;
  s.push(v_start);
  std::fill(visited.begin(), visited.end(), false);
  visited[v_start] = true;
  // ====================================================================================
  // Find cycles and remove vertex into it that was in path
  // ====================================================================================
  struct DeleteStatus {
    int d_c = 0;
    bool deleted = false;
  };
  std::vector<DeleteStatus> deleted(len_path);
  for (int i = 0; i < len_path - 1; ++i) {
    s.push(path[i]);
    while (!s.empty()) {
      auto v = s.top();
      s.pop();
      for (int adj : g[v]) {
        if (v_to_pos.find(adj) != v_to_pos.end()) {
          auto start_index = v_to_pos[path[i]];
          auto end_index = v_to_pos[adj];
          if (end_index - start_index > 2) {
            deleted[start_index + 1].d_c -= 1;
            deleted[end_index - 1].d_c += 1;
          } else if (end_index - start_index == 2) {
            deleted[start_index + 1].deleted = true;
          }
        } else if (!visited[adj]) {
          s.push(adj);
          visited[adj] = true;
        }
      }
    }
  }

  // ====================================================================================
  // Find all vertex, that not contained in any cycles
  // ====================================================================================
  std::vector<int> res;
  res.reserve(n);
  int d_c = 0;
  for (int i = 1; i < len_path - 1; ++i) {
    if (deleted[i].d_c != 0)
      d_c += deleted[i].d_c;
    else {
      if (d_c == 0 && !deleted[i].deleted)
        res.push_back(path[i] + 1);
    }
  }
  out << res.size();
  if (!res.empty()) {
    out << '\n';
    std::sort(res.begin(), res.end());
    std::copy(res.begin(), res.end() - 1, std::ostream_iterator<int>(out, " "));
    out << res.back();
  }
}

void Test(){{std::istringstream in("4 3 1 4\n"
                                   "1 2\n"
                                   "2 3\n"
                                   "3 4");
std::ostringstream out;
KingAssassination(in, out);
//        std::cout << out.str();
//        auto s = out.str();
assert(out.str() == "2\n"
                    "2 3");
}
{
  std::istringstream in("4 4 1 4\n"
                        "1 2\n"
                        "2 3\n"
                        "3 4\n"
                        "1 3");
  std::ostringstream out;
  KingAssassination(in, out);
  //        std::cout << out.str();
  assert(out.str() == "1\n"
                      "3");
}
{
  std::istringstream in("6 8 1 5\n"
                        "1 2\n"
                        "2 3\n"
                        "3 4\n"
                        "4 5\n"
                        "1 6\n"
                        "6 1\n"
                        "6 5\n"
                        "6 4");
  std::ostringstream out;
  KingAssassination(in, out);
  //        std::cout << out.str();
  assert(out.str() == "0");
}
{
  std::istringstream in("14 17 1 14\n"
                        "1 2\n"
                        "1 3\n"
                        "1 4\n"
                        "2 5\n"
                        "3 6\n"
                        "4 9\n"
                        "5 7\n"
                        "6 7\n"
                        "6 4\n"
                        "7 8\n"
                        "7 10\n"
                        "8 9\n"
                        "8 11\n"
                        "9 12\n"
                        "11 13\n"
                        "12 13\n"
                        "13 14");
  std::ostringstream out;
  KingAssassination(in, out);
  //        std::cout << out.str();
  assert(out.str() == "1\n"
                      "13");
}
{
  std::istringstream in("8 8 1 8\n"
                        "1 2\n"
                        "2 3\n"
                        "3 4\n"
                        "3 5\n"
                        "4 6\n"
                        "5 6\n"
                        "6 7\n"
                        "7 8");
  std::ostringstream out;
  KingAssassination(in, out);
  //        std::cout << out.str();
  assert(out.str() == "4\n"
                      "2 3 6 7");
}
{
  std::istringstream in("10 11 1 10\n"
                        "1 2\n"
                        "2 4\n"
                        "2 3\n"
                        "4 5\n"
                        "3 5\n"
                        "5 6\n"
                        "6 7\n"
                        "6 8\n"
                        "7 9\n"
                        "8 9\n"
                        "9 10");
  std::ostringstream out;
  KingAssassination(in, out);
  //        std::cout << out.str();
  assert(out.str() == "4\n"
                      "2 5 6 9");
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //    Test();
  KingAssassination(std::cin, std::cout);
}
