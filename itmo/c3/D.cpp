#include <cassert>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

vector<vector<int>> adj, adj_t;
vector<bool> used;
vector<int> order, comp;
vector<bool> assignment;

vector<int> w;

void dfs1(int v) {
  used[v] = true;
  for (int u : adj[v]) {
    if (!used[u])
      dfs1(u);
  }
  order.push_back(v);
}

void dfs2(int v, int cl) {
  comp[v] = cl;
  for (int u : adj_t[v]) {
    if (comp[u] == -1)
      dfs2(u, cl);
  }
}

bool solve_2SAT(int n) {
  order.clear();
  used.assign(n, false);
  for (int i = 0; i < n; ++i) {
    if (!used[i])
      dfs1(i);
  }

  comp.assign(n, -1);
  for (int i = 0, j = 0; i < n; ++i) {
    int v = order[n - i - 1];
    if (comp[v] == -1)
      dfs2(v, j++);
  }

  assignment.assign(n / 2, false);
  for (int i = 0; i < n; i += 2) {
    if (comp[i] == comp[i + 1])
      return false;
    assignment[i / 2] = comp[i] > comp[i + 1];
  }
  return true;
}

void add(int from, bool nf, int to, bool nt) {
  from = 2 * from ^ nf;
  to = 2 * to ^ nt;
  int n_from = from ^ 1;
  int n_to = to ^ 1;
  adj[n_from].push_back(to);
  adj[n_to].push_back(from);
  adj_t[to].push_back(n_from);
  adj_t[from].push_back(n_to);
}

void clear() {
  w.clear();
  adj.clear();
  adj_t.clear();
  used.clear();
  order.clear();
  comp.clear();
  assignment.clear();
}

/*
 * Строим исходный граф. Запускаем на нём поиск компонент сильной связанности.
 * Строим конденсацию. Далее в конденсации строим топ. сорт. (тот дфс строит уже
 * в топ. сорте) В каждой паре компонент, тот что правее делаем единичкой.
 */
void Task_D(std::istream &in, ostream &out) {
  int n;
  in >> n;

  w.resize(n + 1);
  for (int i = 1; i <= n; ++i) {
    in >> w[i];
  }

  adj.resize(2 * n);
  adj_t.resize(2 * n);
  used.resize(2 * n);
  order.resize(2 * n);
  comp.resize(2 * n);
  assignment.resize(2 * n, false);

  unordered_map<int, int> w_t_i;
  unordered_map<int, pair<int, int>> w_t_i2;
  pair<int, bool> prev;
  in >> prev.first;
  prev.second = false;
  auto first = prev;
  int index = 1;
  w_t_i[prev.first] = 0;
  w_t_i2[prev.first] = make_pair(0, 0);
  for (int i = 1; i < 2 * n; ++i) {
    int curr;
    in >> curr;
    bool is_neg = false;
    if (w_t_i.find(curr) != w_t_i.end()) {
      is_neg = true;
      w_t_i2[curr].second = i;
    } else {
      w_t_i[curr] = index;
      w_t_i2[curr] = make_pair(i, 0);
      add(index, true, index, false);
      ++index;
    }
    if (prev.first != curr && w[prev.first] == w[curr]) {
      add(w_t_i.at(curr), !is_neg, w_t_i.at(prev.first), !prev.second);
    }
    prev = make_pair(curr, is_neg);
  }
  if (first.first != prev.first && w[first.first] == w[prev.first]) {
    add(w_t_i.at(prev.first), !prev.second, 0, true);
  }

  if (!solve_2SAT(2 * n)) {
    out << "NO";
  } else {
    out << "YES\n";
    for (int i = 1; i <= n; ++i) {
      auto idx = w_t_i.at(i);
      out << (assignment[idx] ? w_t_i2.at(i).first : w_t_i2.at(i).second) + 1
          << " ";
    }
  }
}

void Test() {
  {
    istringstream in("2\n"
                     "1 1\n"
                     "1 1 2 2");
    ostringstream out;
    Task_D(in, out);
    //        cout << out.str();
    assert(out.str() == "YES\n"
                        "1 3 ");
  }
  clear();
  {
    istringstream in("2\n"
                     "1 1\n"
                     "1 2 1 2");
    ostringstream out;
    Task_D(in, out);
    assert(out.str() == "NO");
  }
  clear();
  {
    istringstream in("2\n"
                     "1 2\n"
                     "1 2 1 2");
    ostringstream out;
    Task_D(in, out);
    //        cout << out.str();
    assert(out.str() == "YES\n1 2 ");
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  // Test();
  Task_D(cin, cout);
  return 0;
}
