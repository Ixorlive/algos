#include <algorithm>
#include <iostream>
#include <iterator>
#include <queue>

struct Schoolchild {
  int hi;
  int li;
  int index;
};

bool operator<(const Schoolchild &a, const Schoolchild &b) {
  return a.hi + a.li < b.hi + b.li;
}

struct HeightCompare {
  bool operator()(const Schoolchild &a, const Schoolchild &b) const {
    return a.hi < b.hi;
  }
};

int main() {
  int N;
  long long H;
  std::cin >> N;

  long long S = 0;
  std::vector<Schoolchild> schoolchildren;
  for (int i = 0; i < N; i++) {
    int hi, li;
    std::cin >> hi >> li;
    schoolchildren.push_back({hi, li, i + 1});
    S += hi;
  }
  std::cin >> H;
  std::sort(schoolchildren.begin(), schoolchildren.end());

  std::priority_queue<Schoolchild, std::vector<Schoolchild>, HeightCompare> pq;
  long long height = 0;
  std::vector<int> result;
  for (int i = 0; i < N; i++) {
    if (S - height + schoolchildren[i].li >= H) {
      result.push_back(schoolchildren[i].index);
      height += schoolchildren[i].hi;
      pq.push(schoolchildren[i]);
    } else {
      if (pq.empty())
        continue;
      if (S - height + pq.top().hi + schoolchildren[i].li >= H &&
          pq.top().hi > schoolchildren[i].hi) {
        auto it = std::find(result.begin(), result.end(), pq.top().index);
        result.erase(it);
        result.push_back(schoolchildren[i].index);
        height += schoolchildren[i].hi - pq.top().hi;
        pq.pop();
        pq.push(schoolchildren[i]);
      }
    }
  }

  std::cout << result.size();
  if (!result.empty()) {
    std::cout << '\n';
    std::copy(result.begin(), result.end() - 1,
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << result.back();
  }

  return 0;
}
