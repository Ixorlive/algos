#include <bits/stdc++.h>

using namespace std;

void solve(istream &in, std::ostream &out) {
  int k;
  in >> k;
  string s;
  in >> s;
  if (k > s.size() - 1) {
    out << s.size();
    return;
  }
  int set[26]{0};
  for (size_t i = 0; i < k + 1; i++) {
    set[s[i] - 'a']++;
  }
  int l = 0;
  size_t max_len = k + 1;
  for (size_t r = k + 1; r < s.size(); r++) {
    set[s[r] - 'a']++;
    int mmax = 0;
    for (size_t i = 0; i < 26; i++) {
      mmax = max(set[i], mmax);
    }
    if (r - l + 1 - mmax > k) {
      set[s[l] - 'a']--;
      ++l;
    }
    max_len = max(max_len, r - l + 1);
  }
  out << max_len;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"2 abcaz ", "2 helto"};
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
