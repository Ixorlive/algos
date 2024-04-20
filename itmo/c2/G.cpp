#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

struct Point {
  int x;
  int y;

  [[nodiscard]] double dist(const Point &point) const {
    return std::sqrt(((x - point.x) * (x - point.x)) +
                     ((y - point.y) * (y - point.y)));
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t V;
  std::cin >> V;
  if (V == 0)
    return 0;
  std::vector<Point> points(V);
  for (int i = 0; i < V; ++i) {
    std::cin >> points[i].x >> points[i].y;
  }
  if (V == 1) {
    std::cout << "0\n0";
    return 0;
  }

  std::vector<std::vector<double>> dists(V, std::vector<double>(V));
  for (int i = 0; i < V - 1; ++i) {
    for (int j = i + 1; j < V; ++j) {
      dists[i][j] = points[i].dist(points[j]);
      dists[j][i] = dists[i][j];
    }
  }

  int root[V];
  bool visited[V];
  double keys[V];

  for (int i = 0; i < V; ++i) {
    keys[i] = 2 * 2000 * 2000;
    visited[i] = false;
  }

  keys[0] = 0.0;
  root[0] = -1;

  auto get_min_key = [&]() {
    double min = 2 * 2000 * 2000;
    int index;
    for (int i = 0; i < V; ++i) {
      if (!visited[i] && keys[i] < min) {
        min = keys[i];
        index = i;
      }
    }
    return std::make_pair(index, min);
  };

  for (int i = 0; i < V - 1; ++i) {
    auto [u, min_dist] = get_min_key();
    visited[u] = true;

    for (int v = 0; v < V; ++v) {
      if (u != v && !visited[v] && dists[u][v] < keys[v]) {
        root[v] = u;
        keys[v] = dists[u][v];
      }
    }
  }
  double total_length = 0.0;
  for (int i = 1; i < V; ++i) {
    total_length += dists[root[i]][i];
  }

  std::cout.setf(std::ios::fixed, std::ios::floatfield);
  std::cout << std::setprecision(6) << total_length << '\n' << V - 1 << '\n';
  bool first = true;
  for (int i = 1; i < V; ++i) {
    std::cout << (first ? "" : "\n") << root[i] + 1 << ' ' << (i + 1);
    first = false;
  }

  return 0;
}
