#include <bits/stdc++.h>

using namespace std;

int shiftleft(int val) {
  int a = val / 1000;
  int r = val % 1000;
  return r * 10 + a;
}
int shiftright(int val) {
  int d = val % 10;
  int r = val / 10;
  return d * 1000 + r;
}

int inc(int val) {
  int f = val / 1000;
  if (f < 9) {
    return val + 1000;
  }
  return val;
}

int dec(int val) {
  int l = val % 10;
  if (l > 1) {
    return val - 1;
  }
  return val;
}

void solve(istream &in, std::ostream &out) {
  int n;
  int res;
  in >> n >> res;
  if (res == n) {
    out << res;
    return;
  }
  int vis[10001] = {0};
  int path[10001] = {0};
  queue<int> q;
  q.push(n);
  vis[n] = 1;
  path[n] = -1;
  bool stop = false;
  while (!stop && !q.empty()) {
    auto v = q.front();
    q.pop();
    int vs[4] = {inc(v), dec(v), shiftright(v), shiftleft(v)};
    for (size_t i = 0; i < 4; i++) {
      if (vs[i] == res) {
        path[vs[i]] = v;
        stop = true;
        break;
      }
      if (!vis[vs[i]]) {
        q.push(vs[i]);
        vis[vs[i]] = 1;
        path[vs[i]] = v;
      }
    }
  }
  vector<int> respath;
  respath.reserve(10000);
  while (res != -1) {
    respath.push_back(res);
    res = path[res];
  }
  copy(respath.rbegin(), respath.rend(), ostream_iterator<int>(out, "\n"));
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"1234 4321 "};
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
