#include <bits/stdc++.h>

using namespace std;

bool valid(string_view s) {
  stack<string_view> st;
  int i = 0;
  while (i < s.length()) {
    if (s[i] != '<') {
      return false;
    }
    ++i;
    bool close = false;
    if (s[i] == '/') {
      close = true;
      ++i;
    }
    size_t f = i;
    while (f != s.size()) {
      if (s[f] == '>')
        break;
      if (s[f] < 'a' || s[f] > 'z') {
        return false;
      }
      ++f;
    }
    if (f == s.size()) {
      return false;
    }
    string_view tag = s.substr(i, f - i);
    i = f + 1;
    if (close) {
      if (st.empty() || st.top() != tag) {
        return false;
      }
      st.pop();
    } else {
      st.push(tag);
    }
  }
  return st.empty() && i == s.length();
}

void solve(istream &in, std::ostream &out) {
  string s;
  char chrs[26 + 3];
  int j = 0;
  for (char i = 'a'; i <= 'z'; i++) {
    chrs[j++] = i;
  }
  chrs[j++] = '<';
  chrs[j++] = '>';
  chrs[j++] = '/';
  in >> s;
  for (size_t i = 0; i < s.size(); i++) {
    char c = s[i];
    for (j = 0; j < 29; j++) {
      if (chrs[j] == c)
        continue;
      s[i] = chrs[j];
      if (valid(s)) {
        out << s;
        return;
      }
    }
    s[i] = c;
  }
  out << "AIAII";
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"<a></b> ", "<a><aa> ", "<a><>a> ", "<a/</a> "};
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
