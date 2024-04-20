#include <cstring>
#include <iostream>
#include <random>
#include <sstream>
#include <stack>
#include <utility>

typedef uint64_t ui64;
typedef int64_t i64;
using namespace std;

constexpr int kN = 1e5;

minstd_rand gen;

struct Node {
  Node *left = nullptr, *right = nullptr, *p = nullptr;
  i64 prior;
  bool isLoop = false;
  ui64 size = 1;
  int value;
  bool rev = false;
  explicit Node(int val) : prior(rand()), value(val) {}
};

Node *ns[kN + 1];
Node *st[kN + 1];

ui64 get_size(Node *node) { return node ? node->size : 0; }

void push(Node *node) {
  if (node && node->rev) {
    node->rev = false;
    swap(node->left, node->right);
    if (node->left)
      node->left->rev ^= 1;
    if (node->right)
      node->right->rev ^= 1;
  }
}

void update(Node *node) {
  if (!node)
    return;
  node->size = get_size(node->left) + get_size(node->right) + 1;
}

Node *merge(Node *l, Node *r) {
  push(l), push(r);
  if (!l || !r)
    return l ? l : r;
  if (l->prior > r->prior) {
    l->right = merge(l->right, r);
    if (l->right)
      l->right->p = l;
    update(l);
    return l;
  }
  r->left = merge(l, r->left);
  if (r->left)
    r->left->p = r;
  update(r);
  return r;
}

void split(Node *node, int i, Node *&l, Node *&r) {
  if (!node) {
    l = r = nullptr;
    return;
  }
  push(node);
  if (get_size(node->left) < i) {
    split(node->right, i - get_size(node->left) - 1, node->right, r);
    if (node->right)
      node->right->p = node;
    if (r)
      r->p = nullptr;
    l = node;
  } else {
    split(node->left, i, l, node->left);
    if (node->left)
      node->left->p = node;
    if (l)
      l->p = nullptr;
    r = node;
  }
  update(node);
}

pair<Node *, int> getRootAndPos(Node *node) {
  auto *curr = node;
  int ind = 0;
  st[ind] = node;
  while (curr->p) {
    st[++ind] = curr->p;
    curr = curr->p;
  }
  int pos = 0;
  while (true) {
    auto *nd = st[ind];
    --ind;
    push(nd);
    if (ind == -1) {
      pos += get_size(nd->left);
      break;
    }
    if (nd->right == st[ind]) {
      pos += get_size(nd->left) + 1;
    }
  }
  return make_pair(curr, pos);
}
// 3 - 1 - 2 - 4 - 5
// 5
void addRoad(int f, int t) {
  auto [rf, pf] = getRootAndPos(ns[f]);
  auto [rt, pt] = getRootAndPos(ns[t]);

  if (rf == rt) {
    rf->isLoop = true;
  } else {
    if (pf == 0 && pt == 0)
      rf->rev ^= 1;
    else if (pf != 0 && pt != 0)
      rt->rev ^= 1;
    else if (pf == 0)
      swap(rf, rt);
    rf = merge(rf, rt);
  }
}

void destroyRoad(int f, int t) {
  auto [rf, pf] = getRootAndPos(ns[f]);
  auto [rt, pt] = getRootAndPos(ns[t]);

  if (rf != rt)
    return;
  if (rf->isLoop) {
    rf->isLoop = false;
    if (pf > pt)
      swap(pf, pt);
    if (pf == 0 && pt != 1)
      return;
    Node *l, *r;
    split(rf, pf + 1, l, r);
    rt = rf = merge(r, l);
  } else {
    split(rf, min(pf, pt) + 1, rf, rt);
  }
}

i64 getDistance(int f, int t) {
  if (f == t)
    return 0;
  auto [rf, pf] = getRootAndPos(ns[f]);
  auto [rt, pt] = getRootAndPos(ns[t]);

  if (rf != rt)
    return -1;
  ui64 dist = abs(pf - pt);
  if (rf->isLoop) {
    dist = min(dist, get_size(rf) - dist);
  }
  return dist - 1;
}

void solve(std::istream &in, std::ostream &out) {
  int n, m, q;
  in >> n >> m >> q;
  for (size_t i = 1; i <= n; i++) {
    ns[i] = new Node(i);
  }
  int f, t;
  for (size_t i = 0; i < m; i++) {
    in >> f >> t;
    addRoad(f, t);
  }
  char type;
  for (size_t i = 0; i < q; i++) {
    in >> type >> f >> t;
    if (type == '?') {
      out << getDistance(f, t) << '\n';
    } else if (type == '+') {
      addRoad(f, t);
    } else {
      destroyRoad(f, t);
    }
  }
}

void run_test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  // run_test();
  solve(std::cin, std::cout);
}

void run_test() {
  // 5 - 3 - 1 - 2 - 4 - 6
  // vector<string> inputs = {string("10 5 1\n"
  //                                 "1 2\n"
  //                                 "1 3\n"
  //                                 "2 4\n"
  //                                 "3 5\n"
  //                                 "4 6\n"
  //                                 "? 1 6\n"
  //                                 "+ 1 7\n"
  //                                 "+ 5 8\n"
  //                                 "- 2 4\n"
  //                                 "? 1 6\n"
  //                                 "- 1 7\n"
  //                                 "+ 3 9\n"
  //                                 "? 1 9\n"
  //                                 "? 1 8")};
  vector<string> inputs = {string("5 4 6\n"
                                  "1 2\n"
                                  "2 3\n"
                                  "1 3\n"
                                  "4 5\n"
                                  "? 1 2\n"
                                  "? 1 5\n"
                                  "- 2 3\n"
                                  "? 2 3\n"
                                  "+ 2 4\n"
                                  "? 1 5"),
                           string("10 7 11\n"
                                  "1 2\n"
                                  "1 3\n"
                                  "4 5\n"
                                  "4 8\n"
                                  "8 9\n"
                                  "6 7\n"
                                  "7 10\n"
                                  "? 6 7\n"
                                  "? 5 9\n"
                                  "+ 3 6\n"
                                  "? 2 10\n"
                                  "? 7 10\n"
                                  "? 3 9\n"
                                  "? 4 2\n"
                                  "- 3 6\n"
                                  "+ 9 2\n"
                                  "? 3 5\n"
                                  "? 3 6")};
  auto outputs = {0};
  for (auto &input : inputs) {
    std::istringstream in(input);
    std::ostringstream out;
    solve(in, out);
    std::cout << out.str();
  }
};
