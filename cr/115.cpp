#include <bits/stdc++.h>

using namespace std;

size_t getd(int d, int m, int y) {
  int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int y2 = y - 1;
  size_t total_days = y2 * 365 + (y2 / 4 - y2 / 100 + y2 / 400);
  for (size_t i = 1; i < m; i++) {
    total_days += days_in_month[i - 1];
  }
  if (m > 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)) {
    total_days++;
  }
  total_days += d - 1;
  return total_days;
}

constexpr int MAXN = 1e4;
struct person {
  size_t s, e, id;
  bool operator<(const person &p) const { return e > p.e; }
  bool operator==(const person &p) const {
    return p.s == s && p.e == e && p.id == id;
  }
};

ostream &operator<<(ostream &out, const person &p) { return out << p.id; }

person a[MAXN + 2];

void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  int d, m, y;
  int d2, m2, y2;
  int pos = 0;
  for (size_t i = 0; i < n; i++) {
    in >> d >> m >> y >> d2 >> m2 >> y2;
    int death = getd(d2, m2, y2);
    int death2 = getd(d, m, y + 80);
    int s18 = getd(d, m, y + 18);
    if (death > s18) {
      a[pos].s = s18;
      a[pos].e = death > death2 ? death2 : death;
      a[pos].id = i + 1;
      ++pos;
    }
  }
  if (pos == 0) {
    out << 0;
    return;
  }
  sort(a, a + pos,
       [](const person &p1, const person &p2) { return p1.s < p2.s; });
  priority_queue<person> pq;
  set<int> ids;
  pq.push(a[0]);
  ids.insert(a[0].id);
  for (size_t i = 1; i < pos; i++) {
    bool first = true;
    while (!pq.empty() && a[i].s >= pq.top().e) {
      if (first) {
        copy(ids.begin(), ids.end(), ostream_iterator<int>(out, " "));
        out << '\n';
        first = false;
      }
      ids.erase(pq.top().id);
      pq.pop();
    }
    ids.insert(a[i].id);
    pq.push(a[i]);
  }
  copy(ids.begin(), ids.end(), ostream_iterator<int>(out, " "));
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
      "3 2 5 1988 13 11 2005 1 1 1 1 1 30 1 1 1910 1 1 1990 ",
      "3 2 5 1968 13 11 2005 1 1 1 1 1 30 1 1 1910 1 1 1990 ",
      "3 2 5 1988 13 11 2005 1 1 1 1 1 10 2 1 1910 1 1 1928 "};
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
