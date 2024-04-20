#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;
string s;
int n;
int logn;
constexpr int kM = 4000;
constexpr int kA = 26;
int p[kM];
int c[13][kM];
int lp[kM];
int rp[kM];

void buildSuffixArray() {
  // step 1
  int cnt[kM];
  memset(cnt, 0, kA * sizeof(int));
  auto key = [](char c) { return c - 'a'; };
  for (int i = 0; i < n; ++i)
    ++cnt[key(s[i])];
  for (int i = 1; i < kA; ++i)
    cnt[i] += cnt[i - 1];
  for (int i = 0; i < n; ++i)
    p[--cnt[key(s[i])]] = i;
  c[0][p[0]] = 0;
  int classes = 1;
  for (int i = 1; i < n; ++i) {
    if (s[p[i]] != s[p[i - 1]])
      ++classes;
    c[0][p[i]] = classes - 1;
  }
  int pn[kM], cn[kM];
  // step 2
  int h = 0;
  for (; (1 << h) < n; ++h) {
    for (int i = 0; i < n; ++i) {
      pn[i] = p[i] - (1 << h);
      if (pn[i] < 0)
        pn[i] += n;
    }
    memset(cnt, 0, classes * sizeof(int));
    for (int i = 0; i < n; ++i)
      ++cnt[c[h][pn[i]]];
    for (int i = 1; i < classes; ++i)
      cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; --i)
      p[--cnt[c[h][pn[i]]]] = pn[i];
    cn[p[0]] = 0;
    classes = 1;
    for (int i = 1; i < n; ++i) {
      int mid1 = (p[i] + (1 << h)) % n, mid2 = (p[i - 1] + (1 << h)) % n;
      if (c[h][p[i]] != c[h][p[i - 1]] || c[h][mid1] != c[h][mid2])
        ++classes;
      cn[p[i]] = classes - 1;
    }
    memcpy(c[h + 1], cn, n * sizeof(int));
  }
  logn = h - 1;
}

void findNearestSmallerElements(int a[], int n) {
  stack<int> s;
  for (int i = 0; i < n; ++i) {
    while (!s.empty() && a[s.top()] >= a[i]) {
      s.pop();
    }
    lp[i] = s.empty() ? -1 : s.top();
    s.push(i);
  }
  stack<int> s2;
  for (int i = n - 1; i >= 0; --i) {
    while (!s2.empty() && a[s2.top()] >= a[i]) {
      s2.pop();
    }
    rp[i] = s2.empty() ? -1 : s2.top();
    s2.push(i);
  }
}

int lcp(int i, int j) {
  int ans = 0;
  for (int k = logn; k >= 0; --k)
    if (c[k][i] == c[k][j]) {
      ans += 1 << k;
      i += 1 << k;
      j += 1 << k;
    }
  return ans;
}

struct Action {
  bool type;
  int i, k;
  char c;
  Action *prev{nullptr};
};

// qwertybwertygoabcdqwertygoabc
void solve(istream &in, std::ostream &out) {
  in >> s;
  n = (int)s.length();
  // s += "`";
  buildSuffixArray();
  findNearestSmallerElements(p, n);
  vector<int> dp(n + 1, 0);
  vector<bool> vis(n + 1);
  dp[0] = 1;
  unordered_map<int, int> sp;
  vector<Action *> actions(n + 1);
  for (size_t i = 0; i < n; i++) {
    sp[p[i]] = i;
    actions[i] = new Action();
  }
  actions[0]->type = false;
  actions[0]->c = s[0];
  actions[0]->prev = nullptr;
  for (int i = 1; i < n; i++) {
    int lsml = lp[sp[i]] == -1 ? -1 : lcp(i, p[lp[sp[i]]]);
    int rsml = rp[sp[i]] == -1 ? -1 : lcp(i, p[rp[sp[i]]]);
    if (!vis[i] || dp[i - 1] + 1 < dp[i]) {
      actions[i]->prev = actions[i - 1];
      actions[i]->type = false;
      actions[i]->c = s[i];
      dp[i] = dp[i - 1] + 1;
    }
    if (lsml > 5 || rsml > 5) {
      auto pos = lsml > rsml ? p[lp[sp[i]]] : p[rp[sp[i]]];
      auto count = min(n - i, max(lsml, rsml));
      auto ind = i + count - 1;
      if (!vis[ind] || dp[ind] > dp[i] + 5) {
        actions[ind]->prev = actions[i - 1];
        actions[ind]->i = pos + 1;
        actions[ind]->type = true;
        actions[ind]->k = count;
        dp[ind] = dp[i - 1] + 5;
        vis[ind] = true;
      }
    }
  }
  auto *last_action = actions[n - 1];
  vector<string> res;
  res.reserve(n);
  while (last_action) {
    stringstream ss;
    if (last_action->type) {
      ss << last_action->i << " " << last_action->k;
    } else {
      ss << last_action->c;
    }
    res.push_back(ss.str());
    last_action = last_action->prev;
  }
  out << dp[n - 1] << ' ' << res.size() << '\n';
  for (int i = res.size() - 1; i >= 0; --i) {
    out << res[i] << '\n';
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
  vector<string> inputs{"abcdqwertyqwertyu"}; //, "aaaaaaa"};
  for (int i = 0; i < inputs.size(); ++i) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
