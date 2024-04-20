#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

typedef uint64_t ui64;
typedef int64_t i64;

constexpr int MAX = 100005;
pair<int, ui64> a[MAX];
int bit[MAX + 1];

struct Query {
  ui64 i;
  ui64 x;
  ui64 y;
  i64 val;
  bool first;
  bool operator<(const Query &other) const { return val < other.val; }
};

i64 query(ui64 l) {
  i64 s = 0;
  while (l > 0) {
    s += bit[l];
    l -= (l & (-l));
  }
  return s;
}

void BIT(std::istream &in, std::ostream &out) {
  ui64 n, q;
  in >> n >> q;
  memset(bit, 0, n + 1);
  for (ui64 i = 0; i < n; ++i) {
    in >> a[i].first;
    a[i].second = i;
  }
  sort(a, a + n);
  vector<Query> qs(q * 2);
  for (ui64 i = 0; i < q; ++i) {
    ui64 x, y;
    i64 k, l;
    in >> x >> y >> k >> l;
    --x;
    --y;
    qs[i * 2] = {i, x, y, k - 1, true};
    qs[i * 2 + 1] = {i, x, y, l, false};
  }
  std::sort(qs.begin(), qs.end());
  ui64 c = 0;
  vector<i64> ans(q);
  for (const auto &fq : qs) {
    while (a[c].first <= fq.val && c < n) {
      ui64 x = a[c].second + 1;
      while (x <= n) {
        bit[x] += 1;
        x += (x & (-x));
      }
      ++c;
    }
    i64 res = query(fq.y + 1) - query(fq.x);
    ans[fq.i] += fq.first ? -res : res;
  }
  std::copy(ans.begin(), ans.end(), std::ostream_iterator<i64>(out, "\n"));
}

void Test(){{std::istringstream in{"4 2\n"
                                   "1 2 3 4\n"
                                   "1 2 2 3\n"
                                   "1 3 1 3"};
std::ostringstream out;
BIT(in, out);
cout << out.str();
}
{
  std::istringstream in{"11 3\n"
                        "5 9 8 7 1 2 6 11 3 10 4\n"
                        "2 10 2 7\n"
                        "4 8 1 11\n"
                        "5 7 3 3"};
  std::ostringstream out;
  BIT(in, out);
  cout << out.str();
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //  Test();
  BIT(std::cin, std::cout);
  return 0;
}
