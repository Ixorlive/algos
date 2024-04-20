#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct SurImage {
  int w, h;
  int x, y;
  SurImage(int a, int b, int c, int d) : w(a), h(b), x(c), y(d) {}
};

struct Image {
  int w, h;
  char t;
  int dx, dy;
};

vector<string_view> split(string_view str, string_view delimiter) {
  std::vector<std::string_view> tokens;
  tokens.reserve(5000);
  size_t pos_start = 0, pos_end;

  while ((pos_end = str.find(delimiter, pos_start)) != std::string_view::npos) {
    tokens.emplace_back(str.substr(pos_start, pos_end - pos_start));
    pos_start = pos_end + delimiter.length();
  }

  tokens.emplace_back(str.substr(pos_start));
  return tokens;
}

void solve(istream &in, std::ostream &out) {
  int w, h, c;
  in >> w >> h >> c;
  string res;

  stringstream ss;
  ss << in.rdbuf();
  res = ss.str();
  auto pars = split(res, "\n\n");

  int cur_w = 0;
  int cur_h = 0;
  int h_n = h;
  vector<SurImage> imgs;
  auto next_line = [&](int wq) {
    if (cur_w + wq > w) {
      cur_h += h_n;
      h_n = h;
      cur_w = 0;
      return true;
    }
    return false;
  };
  auto find_pos = [&](int &wq, bool with_space = false) {
    bool removed = false;
    bool f = false;
    while (!f) {
      bool is_next = next_line(wq);
      if (is_next && with_space) {
        wq -= c; // remove space before
        with_space = false;
      }
      f = true;
      if (!imgs.empty()) {
        if (is_next || !removed) {
          auto r =
              remove_if(imgs.begin(), imgs.end(), [&](const SurImage &img) {
                return img.y + img.h <= cur_h;
              });
          imgs.erase(r, imgs.end());
          removed = true;
        }
        for (const auto &img : imgs) {
          if (cur_w + wq > img.x && cur_w < img.x + img.w) {
            cur_w = img.x + img.w;
            f = false;
            if (with_space) {
              wq -= c;
              with_space = false;
            }
            break;
          }
        }
      }
    }
    if (with_space) {
      cur_w += c;
      wq -= c;
    }
  };
  int prev_x, prev_y;
  prev_x = -1;
  bool need_space = false;
  for (const auto &par : pars) {
    string str(par);
    istringstream iss(str);
    string s;
    while (iss >> s) {
      if (s == "(image") {
        Image img;
        bool is_last = false;
        while (!is_last) {
          iss >> s;
          if (s.back() == ')') {
            is_last = true;
            s.pop_back();
          }
          auto pos = s.find('=');
          auto prop = s.substr(0, pos);
          auto val = s.substr(pos + 1);
          if (prop == "layout") {
            img.t = val[0];
          } else if (prop == "dx") {
            img.dx = stoi(val);
          } else if (prop == "dy") {
            img.dy = stoi(val);
          } else if (prop == "width") {
            img.w = stoi(val);
          } else if (prop == "height") {
            img.h = stoi(val);
          }
        }
        if (img.t == 'f') {
          if (prev_x == -1) {
            prev_x = cur_w;
            prev_y = cur_h;
          }
          int pos_x = max(0, prev_x + img.dx);
          int pos_y = prev_y + img.dy;
          if (pos_x + img.w > w) {
            pos_x = w - img.w;
          }
          out << pos_x << ' ' << pos_y << '\n';
          prev_x = pos_x + img.w;
          prev_y = pos_y;
          continue;
        } else {
          auto wq = img.w;
          wq += (!need_space || img.t == 's' ? 0 : c);
          find_pos(wq, need_space && img.t == 'e');
          out << cur_w << ' ' << cur_h << '\n';
          if (img.t == 'e') {
            h_n = max(h_n, img.h);
            need_space = true;
          } else {
            need_space = false;
            imgs.emplace_back(img.w, img.h, cur_w, cur_h);
          }
          cur_w += wq;
        }
      } else {
        int wq = s.size() * c + (need_space ? c : 0);
        find_pos(wq, need_space);
        cur_w += wq;
        need_space = true;
      }
      prev_x = -1;
    }
    prev_x = -1;
    need_space = false;
    // new paragraph
    cur_h += h_n;
    if (!imgs.empty()) {
      auto max = max_element(imgs.begin(), imgs.end(),
                             [](const SurImage &img, const SurImage &img2) {
                               return img.y + img.h < img2.y + img2.h;
                             });
      auto max_h = max->y + max->h;
      if (max_h > cur_h) {
        cur_h = max_h;
      }
      imgs.clear();
    }
    h_n = h;
    cur_w = 0;
  }
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{
      " 120 10 8\nstart (image layout=embedded width=12 height=5) (image "
      "layout=surrounded width=25 height=58) and word is (image "
      "layout=floating dx=18 dy=-15 width=25 height=20) here new (image "
      "layout=embedded width=20 height=22) another (image layout=embedded "
      "width=40 height=19) longword\n\nnew paragraph (image layout=surrounded "
      "width=5 height=30) (image layout=floating width=20 height=35 dx=50 "
      "dy=-16) ",

      "100 2 3\n(image dx=10 dy=11 height=100 width=20 layout=floating)",

      " 1000 2 3\n",

      "100 2 3\n(image dx=-10 dy=11 height=100 width=20 layout=floating) "
      "(image "
      "dx=0 dy=11 height=100 width=20 layout=floating) (image dx=0 dy=11 "
      "height=100 width=20 layout=floating)",

      "100 2 3\n(image dx=90 dy=11 height=100 width=20 layout=floating)",

      "16 2 1\n"
      "four sixxis (image layout=surrounded width=5 height=5) "
      "tri 4our tri (image layout=embedded width=2 height=3) (image "
      "layout=surrounded width=3 height=2) (image layout=embedded width=2 "
      "height=1)"};
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
  } else {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
