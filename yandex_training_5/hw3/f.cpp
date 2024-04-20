#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;

struct Trie {
  Trie *chs[26]{nullptr};
  bool isterm = false;
};

void solve(istream &in, std::ostream &out) {
  string dict_line, text_line;
  getline(in, dict_line);
  getline(in, text_line);
  istringstream dict(dict_line);
  istringstream text(text_line);
  string s;
  Trie root;
  Trie *curr;
  while (dict >> s) {
    curr = &root;
    for (char c : s) {
      if (!curr->chs[c - 97]) {
        curr->chs[c - 97] = new Trie();
      }
      curr = curr->chs[c - 97];
    }
    curr->isterm = true;
  }
  while (text >> s) {
    curr = &root;
    bool found = false;
    int stop = 0;
    for (char c : s) {
      if (!curr->chs[c - 97]) {
        out << s << ' ';
        found = true;
        break;
      }
      curr = curr->chs[c - 97];
      if (curr->isterm) {
        out << s.substr(0, stop + 1) << ' ';
        found = true;
        break;
      }
      ++stop;
    }
    if (!found) {
      out << s << ' ';
    }
  }
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"a b\nabdafb basrt casds dsasa a",
                        "aa bc aaa\na aa aaa bcd abcd "};
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
  } else {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
