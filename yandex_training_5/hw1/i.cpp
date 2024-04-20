#include <iostream>
#include <sstream>
#include <vector>

using namespace std;
bool is_leap(int year) {
  return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int get_d(int year, std::string_view month, int day_in_month) {
  constexpr int days[] = {0,   31,  59,  90,  120, 151,
                          181, 212, 243, 273, 304, 334};

  constexpr const char *months[] = {
      "January", "February", "March",     "April",   "May",      "June",
      "July",    "August",   "September", "October", "November", "December"};

  int m_i = -1;
  for (int i = 0; i < 12; ++i) {
    if (months[i] == month) {
      m_i = i;
      break;
    }
  }
  int res = days[m_i] + day_in_month;
  if (is_leap(year) && m_i > 1)
    res++;
  return res;
}
void solve(istream &in, std::ostream &out) {
  int n, year;
  in >> n >> year;
  int d;
  string s;
  s.reserve(15);
  int ws[367]{0};
  for (size_t i = 0; i < n; i++) {
    in >> d >> s;
    ws[get_d(year, s, d)] = 1;
  }
  in >> s;
  constexpr const char *weeks[] = {"Monday",   "Tuesday", "Wednesday",
                                   "Thursday", "Friday",  "Saturday",
                                   "Sunday"};
  int wi = 0;
  for (size_t i = 0; i < 7; i++) {
    if (s == weeks[i]) {
      wi = i;
      break;
    }
  }
  int max = 0;
  int max_w = 0;
  int min = 400;
  int min_w = 0;
  int t = 1;
  int max_days = (is_leap(year) ? 366 : 365);
  auto f = [&](int week) {
    int worked_days = 0;
    int w = wi;
    for (size_t i = 1; i <= max_days; i++) {
      if (w != week && ws[i] != 1) {
        ++worked_days;
      }
      w = (w + 1) % 7;
    }
    if (worked_days > max) {
      max = worked_days;
      max_w = week;
    }
    if (worked_days < min) {
      min = worked_days;
      min_w = week;
    }
  };
  for (size_t i = 0; i < 7; i++) {
    f(i);
  }
  out << weeks[min_w] << " " << weeks[max_w];
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{" 2 2015 1 January 8 January Thursday ",
                        " 3 2013 1 January 8 January 15 January Tuesday ",
                        "3 2013 6 February 13 February 20 February Tuesday "};
  // int i = 1;
  for (int i = 0; i < inputs.size(); ++i) {
    istringstream in(inputs[i]);
    ostringstream out;
    solve(in, out);
    cout << "+==== Test #" << i + 1 << " ====+\n";
    cout << out.str();
    cout << "\n";
  }
}
