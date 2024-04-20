#include <iostream>

void PrintTrim(std::istream &in, std::ostream &out) {
  char c;
  while (in >> c && c == ' ')
    ;
  while (!in.eof()) {
    out << c;
    c = in.get();
    if (c == ' ' && in >> c) {
      out << ' ';
    }
  }
}

// void Test() {
//     {
//         std::istringstream in("     first    test    we ");
//         std::ostringstream out;
//         PrintTrim(in, out);
//         std::cout << out.str();
//         //assert(out.str() == "first test");
//     }
// };

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  PrintTrim(std::cin, std::cout);
}
