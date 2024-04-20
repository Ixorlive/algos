#include <bits/stdc++.h>

using namespace std;

int calc(bool l, bool r, char op) {
  if (op == '|') {
    return l | r;
  }
  if (op == '^') {
    return l ^ r;
  }
  if (op == '&') {
    return l & r;
  }
  exit(0);
}
int precedence(char op) {
  if (op == '|' || op == '^')
    return 1;
  if (op == '&')
    return 2;
  if (op == '!')
    return 3;

  return 0;
}
void solve(istream &in, ostream &out) {
  stack<bool> nums;
  stack<char> ops;
  char c;
  auto f = [&]() {
    char op = ops.top();
    ops.pop();
    if (op == '!') {
      int val = nums.top();
      nums.pop();
      nums.push(!val);
      return;
    }
    bool r = nums.top();
    nums.pop();
    bool l = nums.top();
    nums.pop();
    nums.push(calc(l, r, op));
  };
  while (in.get(c)) {
    if (isspace(c))
      continue;
    if (isdigit(c)) {
      bool num = c == '1' ? true : false;
      nums.push(num);
      continue;
    }
    if (c == '(') {
      ops.push(c);
      continue;
    }
    if (c == ')') {
      while (!ops.empty() && ops.top() != '(') {
        f();
      }
      ops.pop();
      continue;
    }
    if (c == '|' || c == '^' || c == '&' || c == '!') {
      while (!ops.empty() && precedence(ops.top()) >= precedence(c)) {
        f();
      }
      ops.push(c);
      continue;
    }
  }
  while (!ops.empty()) {
    f();
  }
  out << nums.top();
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"1+(2*2 - 3)", "1+a+1 ",    "1 1 + 2 ",
                        "1+2+3+4",     "1+2+3*4+1", "1+(2))",
                        "+ 2 + 2",     "2 + + 2",   "1 + 2 2 +"};
  int i = 8;
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
