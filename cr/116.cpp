#include <bits/stdc++.h>

using namespace std;

struct W {
  int t, z, y;
};

W a[1004];
size_t result[1004]{0};

void solve(istream &in, std::ostream &out) {
  int m, n;
  in >> m >> n;
  int t, z, y;
  for (size_t i = 0; i < n; i++) {
    in >> a[i].t >> a[i].z >> a[i].y;
  }
  if (m == 0) {
    out << 0 << '\n';
    copy(result, result + n, ostream_iterator<int>(out, " "));
    return;
  }
  auto f = [&](size_t q) {
    size_t res = 0;
    for (size_t i = 0; i < n; i++) {
      auto time = q;
      size_t cycle = a[i].t * a[i].z + a[i].y;
      size_t cycles = time / cycle;
      time %= cycle;
      result[i] = cycles * a[i].z + min(time / a[i].t, (size_t)a[i].z);
      res += result[i];
    }
    return res;
  };
  size_t l = 1;
  size_t r = 105014000;
  while (l < r) {
    size_t mid = (l + r) / 2;
    if (f(mid) < m) {
      l = mid + 1;
    } else {
      r = mid;
    }
  }
  auto m1 = f(l - 1);
  for (size_t i = 0; i < n; i++) {
    auto time = l;
    size_t cycle = a[i].t * a[i].z + a[i].y;
    time %= cycle;
    if (time > a[i].t * a[i].z) {
      continue;
    }
    if (time % a[i].t == 0) {
      result[i]++;
      if (++m1 == m)
        break;
    }
  }
  out << l << '\n';
  copy(result, result + n, ostream_iterator<int>(out, " "));
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"1 2 2 1 1 1 1 2 ", "2 2 1 1 1 1 1 1 ",
                        "8 3 1 2 1 1 1 1 1 1 1 "};
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
