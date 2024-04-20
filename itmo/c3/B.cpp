#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

void IsUniq(std::istream &in, std::ostream &out) {
  size_t n, m;
  in >> n >> m;

  Graph graph(n);
  std::vector<int> in_deg(n, 0);

  for (size_t i = 0; i < m; i++) {
    size_t from_v, to_v;
    in >> from_v >> to_v;
    --from_v;
    --to_v;
    graph[from_v].push_back(to_v);
    ++in_deg[to_v];
  }

  std::vector<int> result;
  result.reserve(n);

  std::set<int> set;

  for (int i = 0; i < n; i++) {
    if (in_deg[i] == 0) {
      set.insert(i);
    }
  }
  while (!set.empty()) {
    if (set.size() > 1) {
      out << "NO";
      return;
    }
    auto node = *set.begin();
    set.erase(set.begin());
    result.push_back(node);
    for (auto chield : graph[node]) {
      --in_deg[chield];
      if (in_deg[chield] == 0) {
        set.insert(chield);
      }
    }
  }
  out << "YES" << std::endl;
  for (auto &el : result) {
    ++el;
  }
  std::copy(result.begin(), result.end(), std::ostream_iterator<int>(out, " "));
}

void Test() {
  {
    std::istringstream in("1 0");
    std::ostringstream out;
    IsUniq(in, out);
    assert(out.str() == "YES\n1");
  }
  {
    std::istringstream in("2 1\n2 1");
    std::ostringstream out;
    IsUniq(in, out);
    assert(out.str() == "YES\n2 1");
  }
  {
    std::istringstream in("3 2\n1 2\n1 3");
    std::ostringstream out;
    IsUniq(in, out);
    assert(out.str() == "NO");
  }
}

int main() {
  // Test();
  IsUniq(std::cin, std::cout);
  return 0;
}
