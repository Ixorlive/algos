#include <bits/stdc++.h>

using namespace std;

int calc(int l, int r, char op) {
  if (op == '+') {
    return l + r;
  }
  if (op == '-') {
    return l - r;
  }
  if (op == '*') {
    return l * r;
  }
  exit(0);
}
int precedence(char op) {
  if (op == '+' || op == '-')
    return 1;
  if (op == '*')
    return 2;
  return 0;
}
void solve(istream &in, ostream &out) {
  stack<int> nums;
  stack<char> ops;
  char c;
  int num;
  auto f = [&]() {
    if (nums.size() < 2 || ops.empty()) {
      out << "WRONG";
      exit(0);
    }
    int r = nums.top();
    nums.pop();
    int l = nums.top();
    nums.pop();
    char op = ops.top();
    ops.pop();
    nums.push(calc(l, r, op));
  };
  while (in.get(c)) {
    if (isspace(c))
      continue;
    if (isdigit(c)) {
      in.putback(c);
      in >> num;
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
      if (ops.empty() || ops.top() != '(') {
        out << "WRONG";
        return;
      }
      ops.pop();
      continue;
    }
    if (c == '+' || c == '-' || c == '*') {
      if (nums.empty()) {
        out << "WRONG";
        return;
      }
      while (!ops.empty() && precedence(ops.top()) >= precedence(c)) {
        f();
      }
      ops.push(c);
      continue;
    }
    if (!in.eof()) {
      out << "WRONG";
      return;
    }
  }
  while (!ops.empty()) {
    if (ops.top() == '(') {
      out << "WRONG";
      return;
    }
    f();
  }
  if (nums.size() != 1) {
    out << "WRONG";
    return;
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
                        "1+2+3+4",     "1+2+3*4+1", "1+(2))"};
  int i = 5;
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
