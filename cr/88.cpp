#include <iostream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  unordered_set<string> dict;
  unordered_map<const string *, unordered_set<int>> ydpos;
  string s;
  for (size_t i = 0; i < n; i++) {
    in >> s;
    int ypos = 0;
    for (char c : s) {
      if (isupper(c)) {
        break;
      }
      ypos++;
    }
    s[ypos] = tolower(s[ypos]);
    auto [it, _] = dict.insert(s);
    ydpos[&(*it)].insert(ypos);
  }
  size_t errs = 0;
  while (in >> s) {
    int ypos = -1;
    bool iserr = false;
    for (size_t i = 0; i < s.size(); i++) {
      if (isupper(s[i])) {
        if (ypos != -1) {
          iserr = true;
          break;
        }
        ypos = i;
      }
    }
    if (iserr || ypos == -1) {
      ++errs;
      continue;
    }
    s[ypos] = tolower(s[ypos]);
    auto it = dict.find(s);
    if (it != dict.end()) {
      auto &st = ydpos[&(*it)];
      if (st.find(ypos) == st.end()) {
        ++errs;
      }
    }
  }
  out << errs;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"4 cAnnot cannOt fOund pAge thE pAge cAnnot be found ",
                        "4 cAnnot cannOt fOund pAge The PAGE cannot be found "};
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
