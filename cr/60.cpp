#include <cstdint>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

using namespace std;

void solve(std::istream &in, std::ostream &out) {
  int n, m;
  in >> n >> m;
  unordered_set<int> anya;
  set<int> anya_sorted;
  set<int> borya;
  set<int> common;
  for (int i = 0; i < n; ++i) {
    int v;
    in >> v;
    anya.insert(v);
  }
  for (int i = 0; i < m; ++i) {
    int v;
    in >> v;
    if (anya.find(v) != anya.end()) {
      anya.erase(v);
      common.insert(v);
    } else {
      borya.insert(v);
    }
  }
  for (auto v : anya) {
    anya_sorted.insert(v);
  }
  out << common.size() << "\n";
  for (const auto &v : common) {
    out << v << ' ';
  }
  out << '\n';
  out << anya.size() << "\n";
  for (const auto &v : anya_sorted) {
    out << v << ' ';
  }
  out << '\n';
  out << borya.size() << "\n";
  for (const auto &v : borya) {
    out << v << ' ';
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  solve(std::cin, std::cout);

  return 0;
}
