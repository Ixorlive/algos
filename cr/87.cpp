#include <bits/stdc++.h>

using namespace std;

void solve(istream &in, std::ostream &out) {
  int g, n;
  in >> g >> n;
  string w, s;
  in >> w >> s;
  if (g > n) {
    out << 0;
    return;
  }
  int set[60]{0};
  for (char c : w) {
    if (set[c - 'A'] == 0)
      set[c - 'A'] = 1;
    set[c - 'A']++;
  }
  size_t res = 0;
  int l = 0;
  for (size_t i = 0; i < s.size();) {
    if (set[s[i] - 'A'] == 0) {
      while (l != i) {
        set[s[l] - 'A']++;
        ++l;
      }
      ++i;
      ++l;
      continue;
    }
    if (set[s[i] - 'A'] == 1) {
      while (l != i && set[s[i] - 'A'] == 1) {
        set[s[l] - 'A']++;
        ++l;
      }
    }
    while (i < n && set[s[i] - 'A'] > 1) {
      set[s[i] - 'A']--;
      ++i;
      if (i - l == g) {
        ++res;
        set[s[l] - 'A']++;
        ++l;
      }
    }
  }
  out << res;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{"4 11 cAda AbrAcadAbRa ", "3 6 abc bacbca"};
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
