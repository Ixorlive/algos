#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <random>
#include <sstream>
#include <unordered_map>
#include <vector>

typedef uint64_t ui64;
typedef int64_t i64;
typedef uint8_t ui8;
using namespace std;

using vi = vector<int>;
using vb = vector<bool>;

constexpr int kMod = (1000 * 1000 * 1000 + 7);

constexpr int kN = 1e6;
constexpr ui8 kNumChars = 10;
int n;
minstd_rand gen;

ui64 k_facs[kN + 2];
unordered_map<int, int> invs;

struct Node {
  Node *left = nullptr, *right = nullptr;
  i64 prior;
  ui64 size = 1;
  int value = 0;
  i64 D = 0;
  ui64 set[kNumChars];
  bool rev = false;
  explicit Node(char val) : prior(gen()), value(val - 'a') {
    memset(set, 0, sizeof(set));
  }
};

ui64 get_size(Node *node) { return node ? node->size : 0; }

void shift(ui64 arr[], int D) {
  reverse(arr, arr + kNumChars);
  reverse(arr, arr + D);
  reverse(arr + D, arr + kNumChars);
}

ui64 modInverse(int A, int M = kMod) {
  if (invs.find(A) != invs.end())
    return invs.at(A);
  auto temp = A;
  int m0 = M;
  int y = 0;
  int x = 1;
  while (A > 1) {
    int q = A / M;
    int t = M;
    M = A % M, A = t;
    t = y;
    y = x - q * y;
    x = t;
  }
  if (x < 0)
    x += m0;
  invs[temp] = x;
  return x;
}

void push(Node *node) {
  if (node) {
    if (node->D) {
      node->value = (node->value + node->D) % kNumChars;
      shift(node->set, node->D % kNumChars);
      if (node->left) {
        node->left->D += node->D;
      }
      if (node->right) {
        node->right->D += node->D;
      }
      node->D = 0;
    }
    if (node->rev) {
      node->rev = false;
      swap(node->left, node->right);
      if (node->left)
        node->left->rev ^= 1;
      if (node->right)
        node->right->rev ^= 1;
    }
  }
}

void update(Node *node) {
  if (!node)
    return;
  node->size = get_size(node->left) + get_size(node->right) + 1;
  if (node->left || node->right) {
    push(node->left), push(node->right);
    for (size_t i = 0; i < kNumChars; i++) {
      node->set[i] = (node->left ? node->left->set[i] : 0) +
                     (node->right ? node->right->set[i] : 0);
    }
  } else {
    memset(node->set, 0, sizeof(node->set));
  }
  node->set[node->value]++;
}

Node *merge(Node *l, Node *r) {
  push(l), push(r);
  if (!l || !r)
    return l ? l : r;
  if (l->prior > r->prior) {
    l->right = merge(l->right, r);
    update(l);
    return l;
  }
  r->left = merge(l, r->left);
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
    l = node;
  } else {
    split(node->left, i, l, node->left);
    r = node;
  }
  update(node);
}

Node *reverse(Node *root, int l, int r) {
  Node *lef, *mid, *rig;
  split(root, l, lef, rig);
  split(rig, r - l + 1, mid, rig);
  mid->rev ^= 1;
  return merge(merge(lef, mid), rig);
}

Node *add(Node *root, int l, int r, int D) {
  D = D % kNumChars;
  Node *lef, *mid, *rig;
  split(root, l, lef, rig);
  split(rig, r - l + 1, mid, rig);
  mid->D = (mid->D + D) % kNumChars;
  return merge(merge(lef, mid), rig);
}

ui64 perm(Node *&root, int l, int r) {
  Node *lef, *mid, *rig;
  split(root, l, lef, rig);
  split(rig, r - l + 1, mid, rig);
  ui64 res = k_facs[mid->size];
  ui64 den = 1;
  for (ui64 i : mid->set) {
    den *= k_facs[i];
    den %= kMod;
  }
  root = merge(merge(lef, mid), rig);
  return (res * modInverse(den)) % kMod;
}

Node *build(const string &s, int L = 0, int R = n) {
  if (L == R)
    return nullptr;
  auto mid = L + ((R - L) >> 1);
  auto *new_node = new Node(s[mid]);
  new_node->left = build(s, L, mid);
  new_node->right = build(s, mid + 1, R);
  update(new_node);
  return new_node;
}

void print(Node *node) {
  if (!node)
    return;
  push(node);
  print(node->left);
  cout << static_cast<char>('a' + node->value) << " ";
  print(node->right);
}

void fillFacs() {
  k_facs[0] = 1, k_facs[1] = 1;
  for (size_t i = 2; i <= n; i++) {
    k_facs[i] = (i * k_facs[i - 1]) % kMod;
  }
}

void solve(std::istream &in, std::ostream &out) {
  string s;
  in >> n >> s;
  fillFacs();
  int q, l, r, d, k;
  in >> k;
  auto *root = build(s);
  for (size_t i = 0; i < k; i++) {
    in >> q >> l >> r;
    --l, --r;
    if (q == -1) {
      root = reverse(root, l, r);
    } else if (q == 0) {
      in >> d;
      root = add(root, l, r, d);
    } else {
      out << perm(root, l, r) << '\n';
    }
  }
}

void run_test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  //
  // run_test();
  solve(std::cin, std::cout);
}

void run_test() {
  vector<string> inputs = {
      string("6\nabcabc\n3\n-1 1 6\n0 1 3 1\n1 1 6"),
  };
  auto outputs = {string("180")};
  for (auto &input : inputs) {
    std::istringstream in(input);
    std::ostringstream out;
    solve(in, out);
    std::cout << out.str();
  }
};
