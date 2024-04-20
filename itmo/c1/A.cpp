#include <cstdint>
#include <iostream>

struct Rectangle {
  std::int64_t x1{};
  std::int64_t y1{};
  std::int64_t x2{};
  std::int64_t y2{};
  [[nodiscard]] std::int64_t Area() const {
    if (x2 <= x1 || y2 <= y1)
      return 0;
    return (x2 - x1) * (y2 - y1);
  }
};

void GetIntersArea(std::istream &in, std::ostream &out) {
  size_t n_rect;
  in >> n_rect;
  if (n_rect == 0) {
    out << 0;
    return;
  }
  using std::max;
  using std::min;
  Rectangle intersection;
  in >> intersection.x1 >> intersection.y1 >> intersection.x2 >>
      intersection.y2;
  for (size_t i = 0; i < n_rect - 1; ++i) {
    Rectangle other_rect;
    in >> other_rect.x1 >> other_rect.y1 >> other_rect.x2 >> other_rect.y2;
    intersection.x1 = max(other_rect.x1, intersection.x1);
    intersection.x2 = min(other_rect.x2, intersection.x2);
    intersection.y1 = max(other_rect.y1, intersection.y1);
    intersection.y2 = min(other_rect.y2, intersection.y2);
    if (intersection.Area() == 0) {
      out << 0;
      return;
    }
  }
  out << intersection.Area();
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  GetIntersArea(std::cin, std::cout);
}
