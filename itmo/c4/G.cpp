#include <iostream>
#include <random>
#include <sstream>
#include <vector>

typedef uint64_t ui64;
using namespace std;

constexpr int kN = 1e6 + 10;
ui64 a[kN];
int n;

minstd_rand gen;

struct Node {
  Node *left{}, *right{};
  ui64 size = 1;
  ui64 value = 0;
  ui64 sum = 0;
  explicit Node(ui64 _value) : value(_value), sum(value) {}
};

ui64 get_sum(Node *node) { return node ? node->sum : 0; }

ui64 get_size(Node *node) { return node ? node->size : 0; }

void update(Node *node) {
  if (!node)
    return;
  node->sum = get_sum(node->left) + get_sum(node->right) + node->value;
  node->size = 1 + get_size(node->left) + get_size(node->right);
}

Node *newNode(Node *l, Node *r, ui64 val) {
  auto *node = new Node(val);
  node->left = l, node->right = r;
  update(node);
  return node;
}

Node *merge(Node *left, Node *right) {
  if (!left || !right)
    return left ? left : right;
  auto size = left->size + right->size;
  if (gen() % size < left->size) {
    return newNode(left->left, merge(left->right, right), left->value);
  }
  return newNode(merge(left, right->left), right->right, right->value);
}

void split(Node *node, ui64 t, Node *&left, Node *&right) {
  if (!node) {
    left = right = nullptr;
    return;
  }
  if (get_size(node->left) < t) {
    Node *l = nullptr;
    split(node->right, t - get_size(node->left) - 1, l, right);
    left = newNode(node->left, l, node->value);
  } else {
    Node *r = nullptr;
    split(node->left, t, left, r);
    right = newNode(r, node->right, node->value);
  }
}

Node *build(ui64 arr[], int L = 0, int R = n) {
  if (L == R)
    return nullptr;
  auto mid = L + ((R - L) >> 1);
  return newNode(build(arr, L, mid), build(arr, mid + 1, R), *(arr + mid));
}

void print(Node *node, ostream &out) {
  if (!node)
    return;
  print(node->left, out);
  out << node->value << " ";
  print(node->right, out);
}

void print(Node *node, int l, int r, ostream &out) {
  Node *ln, *rn, *m, *t;
  split(node, l - 1, ln, rn);
  split(rn, r - l + 1, m, t);
  print(m, out);
  out << '\n';
}

ui64 sum(Node *root, int l, int r) {
  Node *t1, *t2, *t3, *t4;
  split(root, l - 1, t1, t2);
  split(t2, r - l + 1, t3, t4);
  return get_sum(t3);
}

Node *copy(Node *root, int _a, int b, int count) {
  Node *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8;
  split(root, _a - 1, t1, t2);
  split(t2, count, t3, t4);
  split(root, b - 1, t5, t6);
  split(t6, count, t7, t8);
  return merge(merge(t5, t3), t8);
}

void solve(std::istream &in, std::ostream &out) {
  in >> n;
  ui64 A, B, M;
  in >> a[0] >> A >> B >> M;
  for (int i = 1; i < n; ++i) {
    a[i] = (A * a[i - 1] + B) % M;
  }
  auto *root = build(a);
  string q;
  int k, x, y, z;
  in >> k;
  for (int i = 0; i < k; ++i) {
    in >> q;
    if (q[0] == 's') {
      in >> x >> y;
      out << sum(root, x, y) << '\n';
    } else if (q[0] == 'c') {
      in >> x >> y >> z;
      root = copy(root, x, y, z);
    } else {
      in >> x >> y;
      print(root, x, y, out);
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
  vector<string> inputs = {
      string("6\n"
             "1 4 5 7\n"
             "7\n"
             "out 1 6\n"
             "cpy 1 3 2\n"
             "out 1 6\n"
             "sum 1 4\n"
             "cpy 1 2 4\n"
             "out 1 6\n"
             "sum 1 6"),
  };

  for (auto &input : inputs) {
    std::istringstream in(input);
    std::ostringstream out;
    solve(in, out);
    std::cout << out.str();
  }
};
