#include <iostream>
#include <stack>
#include <unordered_map>

void PolandCircuit(std::istream &in, std::ostream &out) {
  std::stack<int64_t> values;
  char c;
  while (in >> c) {
    if (isdigit(c)) {
      values.push(c - '0');
    } else {
      auto second = values.top();
      values.pop();
      auto first = values.top();
      values.pop();
      static std::unordered_map<char, int64_t (*)(int64_t, int64_t)> op_map{
          {'+', [](int64_t lhs, int64_t rhs) { return lhs + rhs; }},
          {'-', [](int64_t lhs, int64_t rhs) { return lhs - rhs; }},
          {'*', [](int64_t lhs, int64_t rhs) { return lhs * rhs; }}};
      values.push(op_map[c](first, second));
    }
  }
  out << values.top();
}

// void Test() {
//     {
//         std::istringstream in("8 9 + 1 7 - *");
//         std::ostringstream out;
//         PolandCircuit(in, out);
//         //std::cout << out.str();
//         assert(out.str() == "-102");
//     }
// };

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  PolandCircuit(std::cin, std::cout);
}
