#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void tlw(string &str) {
  transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void solve(istream &in, std::ostream &out) {
  int n;
  string s;
  s.reserve(100);
  in >> n >> s;
  bool tolow = s[0] == 'n';
  in >> s;
  bool digw = s[0] == 'y';
  unordered_set<string> keyws;
  for (size_t i = 0; i < n; i++) {
    in >> s;
    if (tolow)
      tlw(s);
    keyws.insert(s);
  }
  unordered_map<string, pair<int, int>> map;
  char ch;
  auto process_str = [&](string &s) {
    if (tolow)
      tlw(s);
    if (all_of(s.begin(), s.end(), [](char c) { return isdigit(c); })) {
      return;
    }
    if (!digw && isdigit(s[0]))
      return;
    if (keyws.find(s) != keyws.end())
      return;
    auto [it, _] = map.insert({s, {0, map.size()}});
    it->second.first++;
  };
  s.clear();
  while (in.get(ch)) {
    if (std::isalnum(ch) || ch == '_') {
      s.push_back(ch);
    } else if (!s.empty()) {
      process_str(s);
      s.clear();
    }
  }
  if (!s.empty())
    process_str(s);
  int mmax = -1;
  int maxpos = -1;
  string_view maxstr;
  for (const auto &[str, pr] : map) {
    if (mmax == -1 || pr.first > mmax ||
        (pr.first == mmax && pr.second < maxpos)) {
      mmax = pr.first;
      maxpos = pr.second;
      maxstr = str;
    }
  }
  out << maxstr;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{
      "0 yes no int main() { int a; int b; scanf(\"%d%d\", "
      "&a, &b); printf(\"%d\", a + b); } ",
      "0 yes no #define INT int int main() { INT a, b; scanf(\"%d%d\", &a, "
      "&b); printf(\"%d %d\", a + b, 0); } ",
      "6 no no program var begin end while for program sum; var A, B: integer; "
      "begin read(A, b); writeln(a + b); end. ",
      "1 yes yes _ a = 0h b = 0h c = 0h "};
  int i = -1;
  if (i == -1) {
    for (int i = 0; i < inputs.size(); ++i) {
      istringstream in(inputs[i]);
      ostringstream out;
      solve(in, out);
      cout << "+==== Test #" << i + 1 << " ====+\n";
      cout << out.str();
      cout << "\n";
    }
  } else if (i >= 0 && i < inputs.size()) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  } else {
    cout << "Incorrect test id";
  }
}
