#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

struct Bt {
  int val;
  int h = 1;
  Bt *left = nullptr, *right = nullptr;
  Bt(int a) : val(a) {}
  int getlh() { return left ? left->h : 0; }
  int getrh() { return right ? right->h : 0; }
  void update() { h = max(getlh(), getrh()) + 1; }
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
  root->update();
  return root;
}

bool isavl(Bt *root) {
  if (!root)
    return true;
  if (abs(root->getlh() - root->getrh()) > 1) {
    return false;
  }
  return isavl(root->left) && isavl(root->right);
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
  out << (isavl(bt) ? "YES" : "NO");
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
