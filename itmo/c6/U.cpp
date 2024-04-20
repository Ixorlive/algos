#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

typedef uint64_t ui64;
typedef int64_t i64;
typedef uint32_t ui32;
typedef int32_t i32;
typedef uint16_t ui16;
typedef int16_t i16;
typedef uint8_t ui8;
typedef int8_t i8;
using namespace std;

using vi = vector<int>;

vi prefix(const string &s) {
  auto n = s.length();
  vi pi(n);
  for (size_t i = 1; i < n; i++) {
    int j = pi[i - 1];
    while (j > 0 && s[i] != s[j])
      j = pi[j - 1];
    if (s[i] == s[j])
      j++;
    pi[i] = j;
  }
  return pi;
}

void solve(std::istream &in, std::ostream &out) {
  string s;
  in >> s;
  auto P = prefix(s);
  out << s.size() - P.back();
}

void Test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  solve(std::cin, std::cout);
}

void Test() {
  vector<string> inputs = {"zzz", "bcabcab"};
  auto outputs = {1, 3};
  for (auto &input : inputs) {
    std::istringstream in(input);
    std::ostringstream out;
    solve(in, out);
    std::cout << out.str();
  }
};
