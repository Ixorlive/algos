#include <cstdint>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>

enum class EventType { NEW_GOOD = 1, NEW_PERSON = 2 };

std::istream &operator>>(std::istream &in, EventType &e) {
  int i;
  in >> i;
  e = static_cast<EventType>(i);
  return in;
}

struct Event {
  EventType type{};
  std::uint16_t T{};
  std::uint16_t A{};
};

std::istream &operator>>(std::istream &in, Event &e) {
  in >> e.type >> e.T >> e.A;
  return in;
}

void QueueSimulation(std::istream &in, std::ostream &out) {
  using EventTime = std::uint16_t;
  using GoodID = std::uint16_t;

  size_t n_events;
  in >> n_events;
  std::queue<std::pair<EventTime, GoodID>> queue;
  std::unordered_map<GoodID, size_t> goods;
  bool first = true;
  for (size_t i = 0; i < n_events; ++i) {
    Event e;
    in >> e;
    if (e.type == EventType::NEW_GOOD) {
      if (!queue.empty() && e.A == queue.front().second) {
        out << (first ? "" : " ") << e.T - queue.front().first;
        first = false;
        queue.pop();
        while (!queue.empty()) {
          auto it = goods.find(queue.front().second);
          if (it != goods.end() && it->second > 0) {
            out << ' ' << e.T - queue.front().first;
            --it->second;
            queue.pop();
          } else {
            break;
          }
        }
      } else {
        ++goods[e.A];
      }
    } else if (e.type == EventType::NEW_PERSON) {
      if (queue.empty()) {
        auto it = goods.find(e.A);
        if (it != goods.end() && it->second > 0) {
          out << (first ? "" : " ") << 0;
          --it->second;
          first = false;
        } else {
          queue.push({e.T, e.A});
        }
      } else {
        queue.push({e.T, e.A});
      }
    }
  }
  while (!queue.empty()) {
    out << (first ? "" : " ") << -1;
    first = false;
    queue.pop();
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  QueueSimulation(std::cin, std::cout);
}
