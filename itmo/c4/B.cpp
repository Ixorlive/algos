#include <cassert>
#include <cstdint>
#include <functional>
#include <iostream>
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

template <typename Comp = std::less<>> struct AVL {
  struct Node {
    Node *left = nullptr;
    Node *right = nullptr;
    ui64 height = 1;
    i64 key;
    ui64 sum = key;
    explicit Node(i64 v) : key(v){};
    ui64 left_height() const { return left ? left->height : 0; }
    ui64 right_height() const { return right ? right->height : 0; }
    ui64 left_sum() const { return left ? left->sum : 0; }
    ui64 right_sum() const { return right ? right->sum : 0; }
    void update() {
      height = 1 + max(left_height(), right_height());
      sum = key + left_sum() + right_sum();
    }
    i64 balance() const {
      auto x = left_height();
      auto y = right_height();
      return x < y ? -1 * static_cast<i64>(y - x) : x - y;
    }
  };

  Node *root;

  AVL() = default;

  void insert(i64 key) { root = insert(root, key); }

  void remove(i64 key) { root = remove(root, key); }

  void clear() { clear(root); }

  i64 sum(i64 l, i64 r, i64 lx, i64 rx) const {
    return sum(root, l, r, lx, rx);
  }

  ~AVL() { clear(); }

private:
  i64 sum(Node *node, i64 l, i64 r, i64 lx, i64 rx) const {
    if (!node)
      return 0;
    if (l > r)
      return 0;
    if (l <= lx && rx <= r)
      return node->sum;
    return sum(node->left, l, min(r, node->key), lx, node->key) +
           sum(node->right, max(l, node->key), r, node->key, rx) +
           ((l <= node->key && node->key <= r) ? node->key : 0);
  }

  Comp comp;
  static Node *right_rotate(Node *x) {
    auto y = x->left;
    auto B = y->right;
    y->right = x;
    x->left = B;
    x->update();
    y->update();
    return y;
  }

  static Node *left_rotate(Node *x) {
    auto y = x->right;
    auto B = y->left;
    y->left = x;
    x->right = B;
    x->update();
    y->update();
    return y;
  }

  Node *insert(Node *node, i64 key) {
    if (!node) {
      return new Node(key);
    } else if (comp(key, node->key)) {
      node->left = insert(node->left, key);
    } else if (!comp(key, node->key) && key != node->key) {
      node->right = insert(node->right, key);
    }
    return balance_node(node);
  }

  Node *remove(Node *node, i64 key) {
    if (!node) {
      return node;
    } else if (comp(key, node->key)) {
      node->left = remove(node->left, key);
    } else if (key == node->key) {
      if (!node->left) {
        auto temp = node->right;
        delete node;
        return temp;
      } else if (!node->right) {
        auto temp = node->left;
        delete node;
        return temp;
      }
      auto min_node = get_min_node(node->right);
      node->key = min_node->key;
      node->right = remove(node->right, min_node->key);
    } else {
      node->right = remove(node->right, key);
    }
    return balance_node(node);
  }

  Node *balance_node(Node *node) {
    if (!node)
      return node;
    node->update();
    auto balance = node->balance();
    if (balance > 1) {
      if (node->left->balance() <= -1) {
        node->left = left_rotate(node->left);
      }
      return right_rotate(node);
    }
    if (balance < -1) {
      if (node->right->balance() >= 1) {
        node->right = right_rotate(node->right);
      }
      return left_rotate(node);
    }
    return node;
  }

  Node *get_min_node(Node *node) {
    while (node && node->left) {
      node = node->left;
    }
    return node;
  }

  void clear(Node *node) {
    if (!node)
      return;
    clear(node->left);
    clear(node->right);
    delete (node);
  }
};

constexpr i64 MOD = 1000000000; // 10^9

void SumAgain(std::istream &in, std::ostream &out) {
  i32 n;
  in >> n;
  i64 lx = MOD + 1;
  i64 rx = -1;
  i64 last_sum = 0;
  AVL avl{};
  for (int i = 0; i < n; ++i) {
    char query_type;
    in >> query_type;
    if (query_type == '+') {
      i64 key;
      in >> key;
      avl.insert((key + last_sum) % MOD);
      lx = min(lx, (key + last_sum) % MOD);
      rx = max(rx, (key + last_sum) % MOD);
      last_sum = 0;
    } else {
      i64 l, r;
      in >> l >> r;
      last_sum = avl.sum(l, r, lx, rx);
      out << last_sum << '\n';
    }
  }
}

void Test(){{std::istringstream in{"6\n"
                                   "+ 1\n"
                                   "+ 3\n"
                                   "+ 3\n"
                                   "? 2 4\n"
                                   "+ 1\n"
                                   "? 2 4"};
std::ostringstream out;
SumAgain(in, out);
assert(out.str() == "3\n"
                    "7\n");
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //  Test();
  SumAgain(std::cin, std::cout);
  return 0;
}
