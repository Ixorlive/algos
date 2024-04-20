#include <iostream>
#include <sstream>
#include <vector>

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

vi z_function(const string &s) {
  int n = (int)s.length();
  vi z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
      z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r)
      l = i, r = i + z[i] - 1;
  }
  return z;
}
// toolkit | kitten    kittentoolkit => kittentool or toolkitten |
// toolkitten | kitten
// bab | bab => babbab - bab % ab ?
// abcdabcd
// cda  abc | cdabc # |

void solve(istream &in, std::ostream &out) {
  string s1, s2;
  in >> s1 >> s2;
  string res;
  int min_base = -1;
  for (int i = 0; i < 2; ++i) {
    string s3 = s1 + char(1) + s2;
    auto zf = z_function(s3);
    int l1 = s1.size();
    int l2 = s2.size();
    size_t ind = l2;
    for (size_t i = max(0, l2 - l1); i < l2; i++) {
      if (zf[l1 + 1 + i] == l2 - i) {
        ind = i;
        break;
      }
    }
    for (size_t i = 0; i < ind; i++) {
      s3[i] = s2[i];
    }
    for (size_t i = 0; i < l1; ++i) {
      s3[i + ind] = s1[i];
    }
    s3.resize(ind + l1);
    auto pf = prefix(s3);

    int base = s3.size() - pf.back();
    if (i == 1 && base >= min_base) {
      break;
    }
    min_base = base;
    res = s3.substr(0, base);
    if (i == 0)
      swap(s1, s2);
  }
  out << res;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{};
  for (const auto &input : inputs) {
    istringstream in(input);
    ostringstream out;
    solve(in, out);
    cout << out.str();
  }
}
