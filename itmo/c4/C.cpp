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

i64 min_in_segment(Node *root, i64 l, i64 r) {
  Node *l_tree, *r_tree, *eq;
  split(root, l, l_tree, r_tree);
  split(r_tree, r - l + 1, eq, r_tree);
  i64 res = eq->min_value;
  root = merge(merge(l_tree, eq), r_tree);
  return res;
}

void clear(Node *root) {
  if (!root)
    return;
  clear(root->left);
  clear(root->right);
  delete root;
}

void RMQ(std::istream &in, std::ostream &out) {
  ui32 n;
  in >> n;
  Node *root = nullptr;
  for (ui32 i = 0; i < n; ++i) {
    char q;
    i64 x, y;
    in >> q >> x >> y;
    if (q == '+') {
      root = insert(root, x, y);
    } else {
      out << min_in_segment(root, --x, --y) << '\n';
    }
  }
  clear(root);
}

void Test(){{std::istringstream in{"8\n"
                                   "+ 0 5\n"
                                   "+ 1 3\n"
                                   "+ 1 4\n"
                                   "? 1 2\n"
                                   "+ 0 2\n"
                                   "? 2 4\n"
                                   "+ 4 1\n"
                                   "? 3 5"};
std::ostringstream out;
RMQ(in, out);
cout << out.str();
//    assert(out.str() == "4\n"
//                        "3\n"
//                        "1\n");
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //  Test();
  RMQ(std::cin, std::cout);
  return 0;
}
