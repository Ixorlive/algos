#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct Bt {
  int val;
  Bt *left = nullptr, *right = nullptr;
  Bt(int a) : val(a) {}
  ~Bt() {
    delete left;
    delete right;
  }
};
Bt *add(Bt *root, int a) {
  if (!root) {
    return new Bt(a);
  }
  if (a < root->val) {
    root->left = add(root->left, a);
  } else if (a > root->val) {
    root->right = add(root->right, a);
  }
  return root;
}

void printleafs(Bt *node, ostream &out) {
  if (!node)
    return;
  if (!node->left && !node->right) {
    out << node->val << ' ';
    return;
  }
  printleafs(node->left, out);
  printleafs(node->right, out);
}

void solve(istream &in, std::ostream &out) {
  int a = 1;
  Bt *bt = nullptr;
  while (1) {
    in >> a;
    if (a == 0)
      break;
    bt = add(bt, a);
  }
  printleafs(bt, out);
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{"7 3 2 1 9 5 4 6 8 0"};
  int i = -1;
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
