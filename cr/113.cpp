#include <bits/stdc++.h>

using namespace std;

struct seg {
  size_t s, e;
  bool operator==(const seg &s1) const { return s1.s == s && s1.e == e; }
};

ostream &operator<<(ostream &out, const seg &s) {
  out << "[" << s.s << "," << s.e << "]";
  return out;
}

struct seghash {
  size_t operator()(const seg &s) const { return s.s * (1e9 + 1L) + s.e; }
};

constexpr int MAXN = 2000;

seg ss[MAXN];
seg es[MAXN];

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  size_t l, r;
  for (size_t i = 0; i < n; i++) {
    in >> l >> r;
    ss[i] = {l, r};
    es[i] = {l, r};
  }
  auto sfun = [](auto &s1, auto &s2) { return s1.s < s2.s; };
  auto efun = [](auto &s1, auto &s2) { return s1.e < s2.e; };
  auto e2fun = [](auto &s1, auto &s2) { return s1.e > s2.e; };
  sort(ss, ss + n, sfun);
  sort(es, es + n, efun);
  priority_queue<seg, vector<seg>, decltype(e2fun)> pq1(e2fun);
  unordered_multiset<seg, seghash> set;
  size_t max_clients = 0;
  size_t ads1 = 1, ads2 = 6;
  for (int i = 0; i < n; i++) {
    if (ss[i].e < ss[i].s + 5)
      continue;
    pq1.push(ss[i]);
    set.insert(ss[i]);
    while (pq1.top().e < ss[i].s + 5) {
      set.extract(pq1.top());
      pq1.pop();
    }
    if (set.size() > max_clients) {
      max_clients = set.size();
      ads1 = ss[i].s;
      ads2 = ads1 + 10;
    }
    priority_queue<seg, vector<seg>, decltype(sfun)> pq2(sfun);
    for (int j = n - 1; j >= 0; --j) {
      if (es[j].e - 5 < ss[i].s + 5) {
        break;
      }
      if (set.find(es[j]) != set.end() || es[j].s + 5 > es[j].e)
        continue;
      pq2.push(es[j]);
      while (pq2.top().s > es[j].e - 5) {
        pq2.pop();
      }
      if (set.size() + pq2.size() > max_clients) {
        max_clients = set.size() + pq2.size();
        ads1 = ss[i].s;
        ads2 = es[j].e - 5;
      }
    }
  }
  out << max_clients << ' ' << ads1 << ' ' << ads2;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{
      "4 1 11 1 3 6 15 1 6 ",
      "1 1 10 ",
      "3 1 10 11 20 21 30 ",
      "10 1 2 3 4 5 6 7 8 9 100 10 11 12 13 14 15 16 32 64 70 ",
      "6 1 8 3 10 21 28 23 30 41 48 43 50",
      "5 1 9 1 9 6 11 6 11 6 11 "};
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
