#include <algorithm>
#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

using ll = long long;
constexpr int MAXN = 120;

int n;
double H, S;

struct Point {
  double x, y;
};
Point ps[MAXN];

double gauss(const std::vector<Point> &points) {
  double area = 0.0;
  int n = points.size();
  if (n < 3)
    return 0.0;
  for (int i = 0; i < n; ++i) {
    Point p1 = points[i];
    Point p2 = points[(i + 1) % n];
    area += p1.x * p2.y - p2.x * p1.y;
  }
  return std::abs(area) / 2.0;
}

bool isver(int ind) {
  if (ind == 0 || ind == n + 1)
    return true;
  bool l = ps[ind - 1].y < ps[ind].y;
  return l && (ps[ind + 1].y < ps[ind].y);
}

bool isniz(int ind) {
  if (ind == 0 || ind == n + 1)
    return false;
  return (ps[ind - 1].y > ps[ind].y) && (ps[ind + 1].y > ps[ind].y);
}

struct NizList {
  int ind = -1;
  int left_ver, right_ver;
  double sq = 0.0;
  double cur_sq = 0.0;
  NizList *next = nullptr, *prev = nullptr;
  ~NizList() { delete next; }
};

NizList head;
NizList *last;

double getsq(NizList *niz) {
  vector<Point> points;
  points.reserve(MAXN);
  int l = niz->left_ver;
  int r = niz->right_ver;
  size_t t;
  Point gr;
  if (ps[l].y < ps[r].y) {
    t = r;
    while (ps[t - 1].y > ps[l].y)
      --t;
    gr = {ps[t - 1].x + (ps[t].x - ps[t - 1].x) *
                            ((ps[l].y - ps[t - 1].y) / (ps[t].y - ps[t - 1].y)),
          ps[l].y};
    for (size_t i = l; i < t; i++) {
      points.push_back(ps[i]);
    }
    points.push_back(gr);
  } else {
    t = l;
    while (ps[t + 1].y > ps[r].y)
      ++t;
    gr = {ps[t + 1].x + (ps[t].x - ps[t + 1].x) *
                            ((ps[r].y - ps[t + 1].y) / (ps[t].y - ps[t + 1].y)),
          ps[r].y};
    points.push_back(gr);
    for (size_t i = t + 1; i <= r; i++) {
      points.push_back(ps[i]);
    }
  }
  return gauss(points);
}

void initniz() {
  int start = 0;
  int nizid = -1;
  NizList *cur = &head;
  for (size_t i = 1; i <= n + 1; i++) {
    if (isniz(i)) {
      nizid = i;
    } else if (isver(i)) {
      auto new_niz = new NizList();
      new_niz->ind = nizid;
      new_niz->left_ver = start;
      new_niz->right_ver = i;
      new_niz->cur_sq = H * (ps[i].x - ps[start].x);
      new_niz->sq = getsq(new_niz);
      cur->next = new_niz;
      new_niz->prev = cur;
      cur = cur->next;
      start = i;
    }
  }
  last = cur;
}

void clear(NizList *todel) {
  todel->next = nullptr;
  todel->prev = nullptr;
  delete todel;
}

void pereliv() {
  bool abs = false;
  NizList *cur = last;
  do {
    abs = false;
    // pereliv to left
    while (cur->prev != &head) {
      if (ps[cur->left_ver].y < ps[cur->right_ver].y && cur->sq < cur->cur_sq) {
        cur->prev->cur_sq += (cur->cur_sq - cur->sq);
        cur->cur_sq = cur->sq;
      }
      cur = cur->prev;
    }
    // pereliv to right
    while (cur->next) {
      if (ps[cur->left_ver].y > ps[cur->right_ver].y && cur->sq < cur->cur_sq) {
        auto next = cur->next;
        next->cur_sq += (cur->cur_sq - cur->sq);
        cur->cur_sq = cur->sq;
        if (next->cur_sq > next->sq &&
            ps[next->right_ver].y > ps[next->left_ver].y) {
          abs = true;
          auto new_niz = new NizList();
          new_niz->left_ver = cur->left_ver;
          new_niz->right_ver = next->right_ver;
          new_niz->cur_sq = cur->cur_sq + next->cur_sq;
          new_niz->sq = getsq(new_niz);
          new_niz->next = next->next;
          new_niz->prev = cur->prev;
          new_niz->ind =
              ps[cur->ind].y < ps[next->ind].y ? cur->ind : next->ind;
          auto prev = cur->prev;
          prev->next = new_niz;
          if (next->next) {
            next->next->prev = new_niz;
          }
          clear(cur);
          clear(next);
          cur = new_niz;
        }
      }
      if (cur->next) {
        cur = cur->next;
      }
    }
  } while (abs);
}

double gets(double k, NizList *niz) {
  vector<Point> fig;
  fig.reserve(MAXN);
  int l = niz->left_ver;
  int r = niz->right_ver;
  double h = ps[niz->ind].y + k;
  if (ps[l].y < h || ps[r].y < h) {
    return 1e12;
  }
  while (ps[l + 1].y > h)
    ++l;
  while (ps[r - 1].y > h)
    --r;
  for (size_t i = l + 1; i < r; ++i) {
    if (ps[i].y > h)
      return -1;
  }
  Point leftp, rightp;
  if (l == 0) {
    leftp = {ps[l].x, h};
  } else {
    leftp = {ps[l].x + (ps[l + 1].x - ps[l].x) *
                           ((h - ps[l].y) / (ps[l + 1].y - ps[l].y)),
             h};
  }
  if (r == n + 1) {
    rightp = {ps[n + 1].x, h};
  } else {
    rightp = {ps[r - 1].x + (ps[r].x - ps[r - 1].x) *
                                ((h - ps[r - 1].y) / (ps[r].y - ps[r - 1].y)),
              h};
  }
  fig.push_back(leftp);
  for (size_t i = l + 1; i < r; i++) {
    fig.push_back(ps[i]);
  }
  fig.push_back(rightp);
  return gauss(fig);
}

void solve(istream &in, std::ostream &out) {
  in >> n >> H;
  ++n;
  for (size_t i = 1; i <= n; i++) {
    in >> ps[i].x >> ps[i].y;
  }
  ps[0].x = ps[1].x;
  ps[0].y = 1e11;
  ps[n + 1].x = ps[n].x;
  ps[n + 1].y = 1e11;

  initniz();
  pereliv();
  auto cur = head.next;
  double eps = 0.00001;
  double maxh = -1;
  while (cur) {
    double l = 0;
    // double r = min(ps[cur->left_ver].y, ps[cur->right_ver].y);
    double h1 = ps[cur->left_ver].y - ps[cur->ind].y;
    double h2 = ps[cur->right_ver].y - ps[cur->ind].y;
    double r = fmin(h1, h2);
    double m;
    while (r - l > 2 * eps) {
      m = (l + r) / 2.0;
      auto sfig = gets(m, cur);
      if (fabs(cur->cur_sq - sfig) < eps) {
        maxh = fmax(m, maxh);
        break;
      }
      if (sfig > cur->cur_sq) {
        r = m;
      } else {
        l = m;
      }
    }
    maxh = fmax(maxh, m);
    cur = cur->next;
  }
  out << fixed << round(maxh * 10000) / 10000;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{" 7 7.000 -5 10 -3 4 -1 6 1 -4 4 17 5 3 9 5 12 15 ",
                        "1 6.567 0 0 10 20 ", "2 434677788.200 -4 -9 0 0 6 -8"};
  // vector<string> inputs({"6265505"});
  // 08 - 8599.589305407135
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
  } else {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
