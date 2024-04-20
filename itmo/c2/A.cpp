#include <bitset>
#include <cassert>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

// using Graph = vector<unordered_set<int>>;

const int N = 23;

struct Hasher {
  size_t operator()(const pair<int, int> &p) const {
    auto x1 = h(p.first);
    auto x2 = h(p.second);
    return x1 + x2 * x2 * x2;
  }

private:
  hash<int> h;
};

int n, k, global_ans;
vector<int> global_path;
bitset<N> vis, vis2;
int matrix[N][N];
// int res[N], id[N];
unordered_map<pair<int, int>, int, Hasher> dp;

int g(int v) {
  int result = 1;
  vis2[v] = true;
  for (int i = 1; i <= n; ++i) {
    if (!vis2[i] && matrix[v][i]) {
      result += g(i);
    }
  }
  return result;
}

int dfs(int v, int deep, vector<int> &path) {
  vis[v] = true;
  //    auto key = make_pair(vis.to_ulong(), v);
  //    if (dp.find(key) != dp.end()) {
  //        return dp[key];
  //    }
  auto result = deep;
  path.push_back(v);
  if (global_ans < result) {
    global_ans = result;
    global_path = path;
  }
  //    global_ans = max(global_ans, result);
  vis2 = vis;
  auto cnt = g(v);

  if (deep + cnt - 1 > global_ans) {
    for (int i = 1; i <= n; ++i) {
      if (matrix[v][i] && !vis[i]) {
        result = max(result, dfs(i, deep + 1, path));
      }
    }
  }
  // dp[make_pair(vis.to_ulong(), v)] = result;
  vis[v] = false;
  path.pop_back();
  return result;
}

void Task_A(std::istream &in, ostream &out) {
  int m;
  in >> n >> m;
  global_path.reserve(100);
  for (int i = 0; i < m; ++i) {
    int from, to;
    in >> from >> to;
    //        --from; --to;
    if (from != to) {
      matrix[from][to] = 1;
    }
  }

  for (int i = 1; i <= n; ++i) {
    vector<int> path;
    path.reserve(100);
    vis.reset();
    dfs(i, 0, path);
  }
  out << global_ans << endl;
  if (global_ans == 0) {
    global_path = {1};
  }
  bool first = true;
  for (auto &el : global_path) {
    out << (first ? "" : " ") << el;
    first = false;
  }
}

void Test() {
  {
    istringstream in("3 3\n"
                     "1 2\n"
                     "2 3\n"
                     "3 1");
    ostringstream out;
    Task_A(in, out);
    assert(out.str() == "2\n"
                        "1 2 3");
  }
  {
    istringstream in("4 6\n"
                     "1 2\n"
                     "2 1\n"
                     "2 3\n"
                     "2 4\n"
                     "3 2\n"
                     "4 2");
    ostringstream out;
    Task_A(in, out);
    assert(out.str() == "2\n1 2 3" || out.str() == "2\n1 2 4");
  }
  {
    istringstream in("5 3\n"
                     "3 2\n"
                     "2 2\n"
                     "1 5");
    ostringstream out;
    Task_A(in, out);
    assert(out.str() == "1\n3 2" || out.str() == "1\n1 5");
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  //    istringstream in("5 3\n"
  //                     "3 2\n"
  //                     "2 2\n"
  //                     "1 5");
  //    ostringstream out;
  //    Task_A(in, out);
  //    cout << out.str();
  //    Test();
  Task_A(cin, cout);
  return 0;
}
