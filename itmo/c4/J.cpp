#include <iostream>
#include <sstream>

using namespace std;

#define int long long
const int MAXN = 1e5 + 5;
const int mod = 1e9 + 7;
int bit_pre[MAXN + 5] = {0};
int bit_suf[MAXN + 5] = {0};
int a[MAXN + 5];

void update(int bit[], int i, int v) {
  v %= mod;
  if (v < mod)
    v += mod;
  while (i < MAXN) {
    (bit[i] += v) %= mod;
    i += (i & -i);
  }
}

int query(const int bit[], int i) {
  int sum = 0;
  while (i > 0) {
    (sum += bit[i]) %= mod;
    i -= (i & -i);
  }
  return sum;
}

constexpr int g(char c) { return c - 'a' + 1; }

void IsPalindrome(std::istream &in, std::ostream &out) {
  string s;
  in >> s;
  a[0] = 1;
  auto n = s.size();
  for (int i = 1; i < MAXN; ++i) {
    a[i] = a[i - 1] * 997 % mod;
  }
  for (string::size_type i = 0; i < n; ++i) {
    update(bit_pre, i + 1, g(s[i]) * a[i]);
    update(bit_suf, i + 1, g(s[i]) * a[n - i - 1]);
  }
  int m;
  in >> m;
  for (int i = 0; i < m; ++i) {
    string op;
    in >> op;
    if (op[0] == 'c') {
      int pos;
      char v;
      in >> pos >> v;
      --pos;
      update(bit_pre, pos + 1, -g(s[pos]) * a[pos]);
      update(bit_pre, pos + 1, g(v) * a[pos]);
      update(bit_suf, pos + 1, -g(s[pos]) * a[n - pos - 1]);
      update(bit_suf, pos + 1, g(v) * a[n - pos - 1]);
      s[pos] = v;
    } else {
      int l, r;
      in >> l >> r;
      auto q1 =
          (query(bit_pre, (l + r) / 2) - query(bit_pre, (l - 1)) + mod) % mod;
      auto q2 =
          (query(bit_suf, r) - query(bit_suf, (l + r - 1) / 2) + mod) % mod;
      bool is_palindrome = (q1 * a[n - r] % mod) == (q2 * a[l - 1] % mod);
      out << (is_palindrome ? "Yes" : "No") << '\n';
    }
  }
}

void Test(){//  {
            //    std::istringstream in{"abcda\n"
            //                          "5\n"
            //                          "palindrome? 1 5\n"
            //                          "palindrome? 1 1\n"
            //                          "change 4 b\n"
            //                          "palindrome? 1 5\n"
            //                          "palindrome? 2 4"};
            //    std::ostringstream out;
            //    IsPalindrome(in, out);
            ////    cout << out.str();
            //  }
            {std::istringstream in{"aybabtu\n"
                                   "5\n"
                                   "palindrome? 3 5\n"
                                   "change 3 x\n"
                                   "palindrome? 3 5\n"
                                   "change 5 x\n"
                                   "palindrome? 3 5"};
std::ostringstream out;
IsPalindrome(in, out);
cout << out.str();
}
}
;

signed main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //  Test();
  IsPalindrome(std::cin, std::cout);
}
