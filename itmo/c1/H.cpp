#include <iostream>
#include <set>
#include <unordered_map>

void ForStatisticLove(std::istream &in, std::ostream &out) {
  using CityId = size_t;
  using NumPassengers = size_t;
  size_t n;
  in >> n;
  std::unordered_map<NumPassengers, std::set<CityId>> map;
  for (CityId city_id = 1; city_id <= n; ++city_id) {
    NumPassengers numPassengers;
    in >> numPassengers;
    map[numPassengers].insert(city_id);
  }
  size_t query;
  in >> query;
  std::string result(query, '0');
  for (size_t i = 0; i < query; ++i) {
    size_t l, r;
    NumPassengers passengers;
    in >> l >> r >> passengers;
    auto it = map.find(passengers);
    if (it != map.end()) {
      auto left = it->second.lower_bound(l);
      auto right = it->second.upper_bound(r);
      if (left != right)
        result[i] = '1';
    }
  }
  out << result;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  ForStatisticLove(std::cin, std::cout);
}
