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
    ui64 size = 1;
    explicit Node(i64 v) : key(v){};
    ui64 left_height() const { return left ? left->height : 0; }
    ui64 right_height() const { return right ? right->height : 0; }
    ui64 left_size() const { return left ? left->size : 0; }
    ui64 right_size() const { return right ? right->size : 0; }
    void update() {
      height = 1 + max(left_height(), right_height());
      size = 1 + left_size() + right_size();
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

  i64 find_kth_min(i64 k) const { return find_kth_min(root, k); }

  void clear() { clear(root); }

  ~AVL() { clear(); }

private:
  Comp comp;
  static Node *right_rotate(Node *x) {
    /*
     *  ╭──── x ────╮			  ╭──── y ────╮
        │           │			  │	          x
        y           C			  A      ╭────┴────╮
        │			    ->               B         C
   ╭────┴────╮
   A         B
     */
    auto y = x->left;
    auto B = y->right;
    y->right = x;
    x->left = B;

    x->update();
    y->update();

    return y;
  }

  static Node *left_rotate(Node *x) {
    // left symmetrically
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
    } else {
      node->right = insert(node->right, key);
    }

    node->update();
    auto balance = node->balance();
    if (balance > 1) {
      if (comp(key, node->left->key)) {
        return right_rotate(node);
      }
      node->left = left_rotate(node->left);
      return right_rotate(node);
    }
    if (balance < -1) {
      // key > node->right->key
      if (!comp(key, node->right->key) && key != node->right->key) {
        return left_rotate(node);
      }
      node->right = right_rotate(node->right);
      return left_rotate(node);
    }
    return node;
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
    if (!node)
      return node;
    node->update();
    auto balance = node->balance();
    if (balance > 1) {
      if (node->left->balance() >= 0) {
        return right_rotate(node);
      }
      node->left = left_rotate(node->left);
      return right_rotate(node);
    }
    if (balance < -1) {
      if (node->right->balance() <= 0) {
        return left_rotate(node);
      }
      node->right = right_rotate(node->right);
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

  i64 find_kth_min(Node *node, ui64 k) const {
    if (k == node->left_size() + 1)
      return node->key;
    if (k <= node->left_size())
      return find_kth_min(node->left, k);
    return find_kth_min(node->right, k - node->left_size() - 1);
  }

  void clear(Node *node) {
    if (!node)
      return;
    clear(node->left);
    clear(node->right);
    delete (node);
  }
};

void KMax(std::istream &in, std::ostream &out) {
  ui64 n;
  i32 query_type = 0;
  in >> n;
  AVL<std::greater<>> avl{};
  for (int i = 0; i < n; ++i) {
    //  while(query_type != 2) {
    i64 key;
    in >> query_type >> key;
    if (query_type == -1) {
      avl.remove(key);
    } else if (query_type == 1) {
      avl.insert(key);
    } else {
      out << avl.find_kth_min(key) << '\n';
    }
  }
}

void Test(){{std::istringstream in{"11\n"
                                   "+1 5\n"
                                   "+1 3\n"
                                   "+1 7\n"
                                   "0 1\n"
                                   "0 2\n"
                                   "0 3\n"
                                   "-1 5\n"
                                   "+1 10\n"
                                   "0 1\n"
                                   "0 2\n"
                                   "0 3"};
std::ostringstream out;
KMax(in, out);
assert(out.str() == "7\n"
                    "5\n"
                    "3\n"
                    "10\n"
                    "7\n"
                    "3\n");
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //  Test();
  KMax(std::cin, std::cout);
  return 0;
}
