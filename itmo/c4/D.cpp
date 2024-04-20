#include <climits>
#include <cstdint>
#include <iostream>
#include <random>
#include <sstream>

using namespace std;

typedef uint64_t ui64;
typedef int64_t i64;
typedef uint32_t ui32;
typedef int32_t i32;
typedef uint16_t ui16;
typedef int16_t i16;
typedef uint8_t ui8;
typedef int8_t i8;

minstd_rand gen;

struct Node {
  Node *left{}, *right{};
  i64 prior;
  i64 value = 0;
  ui64 size = 1;
  i64 min_value;
  i64 to_add = 0;
  explicit Node(i64 value) : prior(gen()), value(value), min_value(value) {}
};

i64 get_size(Node *root) { return root ? root->size : 0; }

i64 get_min(Node *root) {
  return root ? root->min_value + root->to_add : INT_MAX;
}

void update(Node *root) {
  if (!root)
    return;
  root->size = 1 + get_size(root->left) + get_size(root->right);
  root->min_value =
      min(min(get_min(root->left), get_min(root->right)), root->value);
}

void push(Node *root) {
  if (root && root->to_add) {
    root->value += root->to_add;
    root->min_value += root->to_add;
    if (root->left)
      root->left->to_add += root->to_add;
    if (root->right)
      root->right->to_add += root->to_add;
    root->to_add = 0;
  }
}

Node *merge(Node *l, Node *r) {
  push(l);
  push(r);
  if (!l || !r)
    return l ? l : r;
  if (l->prior > r->prior) {
    l->right = merge(l->right, r);
    update(l);
    return l;
  } else {
    r->left = merge(l, r->left);
    update(r);
    return r;
  }
}

void split(Node *root, i64 t, Node *&l, Node *&r) {
  push(root);
  if (!root) {
    l = r = nullptr;
    return;
  }
  if (get_size(root->left) < t) {
    split(root->right, t - get_size(root->left) - 1, root->right, r);
    l = root;
  } else {
    split(root->left, t, l, root->left);
    r = root;
  }
  update(l);
  update(r);
}

Node *insert(Node *root, i64 i, i64 v) {
  Node *l, *r;
  split(root, i, l, r);
  return merge(merge(l, new Node(v)), r);
}

Node *push_bask(Node *root, i64 v) { return merge(root, new Node(v)); }

void clear(Node *root) {
  if (!root)
    return;
  clear(root->left);
  clear(root->right);
  delete root;
}

Node *remove(Node *root, i64 i) {
  Node *l_tree, *r_tree, *e_tree;
  split(root, i, l_tree, r_tree);
  split(r_tree, 1, e_tree, r_tree);
  return merge(l_tree, r_tree);
}

i64 get(Node *root, i64 i) {
  Node *l_tree, *r_tree, *e_tree;
  split(root, i, l_tree, r_tree);
  split(r_tree, 1, e_tree, r_tree);
  root = merge(merge(l_tree, e_tree), r_tree);
  return e_tree->value;
}

void ImplicitKey(std::istream &in, std::ostream &out) {
  ui32 n, m;
  in >> n >> m;
  Node *root = nullptr;
  for (ui32 i = 0; i < n; ++i) {
    i64 v;
    in >> v;
    root = push_bask(root, v);
  }
  for (ui32 i = 0; i < m; ++i) {
    std::string q;
    i64 x, y = 0;
    in >> q >> x;
    if (q[0] == 'a') {
      in >> y;
      root = insert(root, x, y);
    } else {
      root = remove(root, --x);
    }
  }
  out << get_size(root) << '\n';
  for (auto i = 0; i < get_size(root); ++i) {
    out << get(root, i) << ' ';
  }
  clear(root);
}

void Test(){{std::istringstream in{"3 4\n"
                                   "1 2 3\n"
                                   "del 3\n"
                                   "add 0 9\n"
                                   "add 3 8\n"
                                   "del 2"};
std::ostringstream out;
ImplicitKey(in, out);
cout << out.str();
//    assert(out.str() == "3\n"
//                        "9 2 8");
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  ImplicitKey(std::cin, std::cout);
  return 0;
}
