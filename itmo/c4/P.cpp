#include <cassert>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

typedef uint64_t ui64;
typedef int64_t i64;
typedef uint32_t ui32;
typedef int32_t i32;
typedef uint16_t ui16;
typedef int16_t i16;
typedef uint8_t ui8;
typedef int8_t i8;

class Stack {
public:
  const Stack *push(i64 _value) const { return new Stack(_value, this); }
  bool empty() const { return !this; }
  i64 top() const {
    assert(this);
    return value;
  }
  const Stack *pop() const {
    assert(this);
    return next;
  }
  static const Stack *null;

private:
  i64 value;
  const Stack *next;
  explicit Stack(i64 _value, const Stack *_next = 0)
      : value(_value), next(_next) {}
};
const Stack *Stack::null = nullptr;

class Queue {
public:
  Queue() : size(0), help2_size(-1) {
    main = help = main2 = help2 = Stack::null;
  }
  const Queue *push(i64 value) const {
    return Queue(size + 1, help2_size, main->push(value), help, main2, help2)
        .morph();
  }
  bool empty() const { return size == 0; }
  i64 top() const { return help->top(); }
  const Queue *pop() const {
    assert(size);
    return Queue(size - 1, help2_size == -1 ? -1 : help2_size - 1, main,
                 help->pop(), main2, help2)
        .morph();
  }

private:
  ui64 size, help2_size;
  const Stack *main, *help, *main2, *help2;
  Queue(ui64 _size, ui64 _help2_size, const Stack *_main, const Stack *_help,
        const Stack *_main2, const Stack *_help2)
      : size(_size), help2_size(_help2_size), main(_main), help(_help),
        main2(_main2), help2(_help2) {}
  Queue *morph() {
    if (help2_size == -1) {
      help2_size = size;
      help2 = Stack::null;
      main2 = main;
    }
    if (help2_size > 0) {
      help2_size--;
      help2 = help2->push(main2->top());
      main2 = main2->pop();
    }
    if (help2_size == 0) {
      help = help2;
      help2_size = -1;
      help2 = main2 = Stack::null;
    }
    return new Queue(size, help2_size, main, help, main2, help2);
  }
};

void PersistentQueue(std::istream &in, std::ostream &out) {
  std::vector<const Queue *> queues;
  queues.emplace_back(new Queue());
  ui64 n;
  in >> n;
  for (ui64 i = 0; i < n; ++i) {
    i16 op;
    ui64 t;
    in >> op >> t;
    if (op == -1) {
      out << queues[t]->top() << '\n';
      queues.push_back(queues[t]->pop());
    } else {
      i64 val;
      in >> val;
      queues.push_back(queues[t]->push(val));
    }
  }
  for (auto *q : queues) {
    delete q;
  }
}

void Test(){{std::istringstream in{"10\n"
                                   "1 0 1\n"
                                   "1 1 2\n"
                                   "1 2 3\n"
                                   "1 2 4\n"
                                   "-1 3\n"
                                   "-1 5\n"
                                   "-1 6\n"
                                   "-1 4\n"
                                   "-1 8\n"
                                   "-1 9"};
std::ostringstream out;
PersistentQueue(in, out);
cout << out.str();
//    assert(out.str() == "1\n"
//                        "2\n"
//                        "3\n"
//                        "1\n"
//                        "2\n"
//                        "4");
}
}
;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  PersistentQueue(std::cin, std::cout);
}
