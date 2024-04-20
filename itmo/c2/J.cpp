#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct Edge {
  int from, to;
  double weight;
};

int find(std::vector<int> &parent, int i) {
  while (parent[i] != i) {
    parent[i] = parent[parent[i]];
    i = parent[i];
  }
  return i;
}

void union_(vector<int> &parent, vector<int> &rank, int x, int y) {
  int xroot = find(parent, x);
  int yroot = find(parent, y);
  if (xroot != yroot) {
    if (rank[xroot] < rank[yroot])
      swap(xroot, yroot);
    parent[yroot] = xroot;
    if (rank[xroot] == rank[yroot])
      ++rank[xroot];
  }
}

void Task_J(std::istream &in, std::ostream &out) {
  int H, N;
  in >> H >> N;

  std::unordered_map<int, pair<int, int>> bumps;

  for (int i = 0; i < N; i++) {
    int x, y;
    in >> x >> y;
    bumps[i] = {x, y};
  }
  bumps[N] = {0, 0};
  bumps[N + 1] = {0, H};

  vector<Edge> edges;
  edges.reserve(N * N);
  for (int i = 0; i < N; ++i) {
    auto [x1, y1] = bumps[i];
    edges.push_back({N, i, static_cast<double>(y1)});
    edges.push_back({i, N + 1, static_cast<double>(H - y1)});
    for (int j = i + 1; j < N; ++j) {
      if (j == i)
        continue;
      auto [x2, y2] = bumps[j];
      double weight = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
      edges.push_back({i, j, weight});
    }
  }

  sort(edges.begin(), edges.end(), [](const Edge &a, const Edge &b) -> bool {
    return a.weight < b.weight;
  });

  // Use a union-find algorithm to find the maximum spanning tree
  std::vector<int> parent(N + 2);
  std::vector<int> rank(N + 2, 0);
  for (int i = 0; i <= N + 1; ++i) {
    parent[i] = i;
  }

  double max_jump = -1.0;
  for (const auto &edge : edges) {
    int x = find(parent, edge.from);
    int y = find(parent, edge.to);
    if (x != y) {
      auto root_one = find(parent, N);
      auto root_two = find(parent, N + 1);
      if ((root_one == x && root_two == y) ||
          (root_two == x && root_one == y)) {
        max_jump = edge.weight;
        break;
      }
      union_(parent, rank, x, y);
    }
  }

  out << max_jump << endl;
}

void Test() {
  {
    std::istringstream in("10 3\n"
                          "1 3\n"
                          "3 7\n"
                          "6 6");
    std::ostringstream out;
    Task_J(in, out);
    std::cout << out.str();
  }
  {
    std::istringstream in("12 3\n"
                          "1 6\n"
                          "5 3\n"
                          "5 9");
    std::ostringstream out;
    Task_J(in, out);
    std::cout << out.str();
  }
  {
    std::istringstream in("7 4\n"
                          "1 2\n"
                          "3 4\n"
                          "5 3\n"
                          "6 5");
    std::ostringstream out;
    Task_J(in, out);
    std::cout << out.str();
  }
  {
    std::istringstream in("5 4\n"
                          "-6 2\n"
                          "2 4\n"
                          "0 2\n"
                          "-7 4");
    std::ostringstream out;
    Task_J(in, out);
    std::cout << out.str();
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout.setf(std::ios::fixed, std::ios::floatfield);
  std::cout << std::setprecision(6);

  //    Test();
  Task_J(std::cin, std::cout);
  return 0;
}
