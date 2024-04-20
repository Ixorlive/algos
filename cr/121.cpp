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

Bt *add(Bt *root, int a, int curh) {
  if (!root) {
    cout << curh << ' ';
    return new Bt(a);
  }
  if (a < root->val) {
    root->left = add(root->left, a, curh + 1);
  } else if (a > root->val) {
    root->right = add(root->right, a, curh + 1);
  }
  return root;
}
void solve(istream &in, std::ostream &out) {
  int a;
  Bt *b = nullptr;
  while (1) {
    in >> a;
    if (a == 0)
      break;
    b = add(b, a, 1);
  }
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
