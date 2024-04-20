#include <bits/stdc++.h>

using namespace std;

using Graph = vector<unordered_set<int>>;
map<string, int> ns;
unordered_map<int, size_t> res;
Graph g;
int n;

size_t f(int v) {
  size_t sum = 0;
  for (const auto &cs : g[v]) {
    sum += f(cs);
  }
  sum += g[v].size();
  res[v] = sum;
  return sum;
}

void solve(istream &in, std::ostream &out) {
  in >> n;
  g.resize(n + 1);
  int id = 0;
  string parent, child;
  unordered_set<int> s;
  for (size_t i = 0; i < n - 1; i++) {
    in >> child >> parent;
    if (ns.find(child) == ns.end()) {
      ns[child] = id++;
    }
    if (ns.find(parent) == ns.end()) {
      ns[parent] = id++;
    }
    g[ns[parent]].insert(ns[child]);
    s.insert(ns[child]);
  }
  int root;
  for (const auto &[_, id] : ns) {
    if (s.find(id) == s.end()) {
      root = id;
      break;
    }
  }
  f(root);
  for (const auto &[str, id] : ns) {
    out << str << ' ' << res[id] << '\n';
  }
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{
      "9 Alexei Peter_I Anna Peter_I Elizabeth Peter_I Peter_II Alexei "
      "Peter_III Anna Paul_I Peter_III Alexander_I Paul_I Nicholaus_I Paul_I ",
      "10 AQHFYP MKFXCLZBT AYKOTYQ QIUKGHWCDC IWCGKHMFM WPLHJL MJVAURUDN "
      "QIUKGHWCDC MKFXCLZBT IWCGKHMFM PUTRIPYHNQ UQNGAXNP QIUKGHWCDC WPLHJL "
      "UQNGAXNP WPLHJL YURTPJNR QIUKGHWCDC ",
      "10 BFNRMLH CSZMPFXBZ CSZMPFXBZ IHWBQDJ FMVQTU FUXATQUGIG FUXATQUGIG "
      "IRVAVMQKN GNVIZ IQGIGUJZ IHWBQDJ LACXYFQHSQ IQGIGUJZ JMUPNYRQD "
      "IRVAVMQKN GNVIZ JMUPNYRQD BFNRMLH "};
  int i = 0;
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
