#include <cstring>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

using namespace std;

int mx[501][501];
int vis[501]{0};
vector<int> path;
int n;

bool dfs(int v, int prev, ostream &out) {
  vis[v] = 1;
  for (size_t i = 0; i < n; i++) {
    if (mx[v][i] && i != v && i != prev) {
      if (vis[i] || !dfs(i, v, out)) {
        if (path.empty()) {
          path.push_back(i + 1);
        }
        if (path[0] == v + 1) {
          out << "YES\n" << path.size() << '\n';
          copy(path.begin(), path.end(), ostream_iterator<int>(out, " "));
        }
        path.push_back(v + 1);
        return false;
      }
    }
  }
  return true;
}

void solve(istream &in, std::ostream &out) {
  in >> n;
  path.reserve(n + 1);
  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j < n; j++) {
      in >> mx[i][j];
    }
  }
  for (size_t i = 0; i < n; i++) {
    if (!vis[i]) {
      if (!dfs(i, -1, out)) {
        return;
      }
    }
  }
  out << "NO";
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{"3 0 1 1 1 0 1 1 1 0 ",
                        "4 0 0 1 0 0 0 0 1 1 0 0 0 0 1 0 0 ",
                        "5 0 1 0 0 0 1 0 0 0 0 0 0 0 1 1 0 0 1 0 1 0 0 1 1 0 "};
  int i = -1;
  if (i == -1) {
    for (int i = 0; i < inputs.size(); ++i) {
      memset(mx, 0, sizeof(mx));
      memset(vis, 0, sizeof(vis));
      path.clear();
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
