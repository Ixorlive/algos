#include <bits/stdc++.h>

using namespace std;

struct Node {
  Node() = default;
  Node(Node *n, int d) : next(n), id(d) {}
  Node *next = nullptr;
  int id;
  ~Node() { delete next; }
};

void print(Node *n, ostream &out) {
  if (n) {
    out << n->id << ' ';
    print(n->next, out);
  } else {
    out << '\n';
  }
}

void solve(istream &in, std::ostream &out) {
  Node *head = nullptr;
  Node *midl = nullptr;
  Node *tail = nullptr;
  int n;
  in >> n;
  char c;
  int id;
  size_t size = 0;
  for (size_t i = 0; i < n; i++) {
    in >> c;
    if (c != '-') {
      in >> id;
      if (size == 0) {
        head = new Node(nullptr, id);
        tail = head;
        midl = head;
      } else {
        if (c == '+') {
          tail->next = new Node(nullptr, id);
          tail = tail->next;
        } else {
          midl->next = new Node(midl->next, id);
          if (size == 1)
            tail = midl->next;
        }
        if (size % 2 == 0)
          midl = midl->next;
      }
      ++size;
    } else {
      if (size % 2 == 0)
        midl = midl->next;
      Node *del = head;
      head = head->next;
      out << del->id << '\n';
      del->next = nullptr;
      delete del;
      --size;
    }
    // print(head, out);
  }
  delete head;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{"7 + 1 + 2 - + 3 + 4 - - "};
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
