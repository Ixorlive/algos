#include <iostream>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct InfoTeam {
  size_t total = 0;
  size_t matches = 0;
};

struct InfoPlayer {
  size_t total_goals = 0;
  size_t total_matches = 0;
  int goals[91]{0};
};

#define MPRINT(map, s, field, default)                                         \
  do {                                                                         \
    auto it = map.find(s);                                                     \
    if (it == map.end()) {                                                     \
      out << default << '\n';                                                  \
    } else {                                                                   \
      out << it->second.field << '\n';                                         \
    }                                                                          \
  } while (0);

enum LineType {
  MATCH_INFO,
  TOTAL_TEAM,
  TOTAL_PLAYER,
  MEAN_TEAM,
  MEAN_PLAYER,
  GOALS_MINUTE,
  GOALS_FIRST,
  GOALS_LAST,
  SCORE_TEAM,
  SCORE_PLAYER,
  UNKNOWN
};

struct ParseResult {
  LineType type = UNKNOWN;
  string s1, s2;
  int t1, t2;
};

ParseResult parse_line(istream &in) {
  string line;
  getline(in, line);
  stringstream ss(line);
  string temp;
  ParseResult result;
  if (line.size() <= 2) {
    return result;
  }

  if (line[0] == '"') {
    getline(ss, result.s1, '"');
    getline(ss, result.s1, '"');
    ss.ignore(256, '"');
    getline(ss, result.s2, '"');
    char t;

    result.type = MATCH_INFO;
    ss >> result.t1 >> t >> result.t2;
  } else {
    ss >> temp;
    switch (temp[0]) {
    case 'T':     // Total
      ss >> temp; // Skip "goals"
      ss >> temp; // Skip "for" or "by"
      result.type = (temp[0] == 'f') ? TOTAL_TEAM : TOTAL_PLAYER;
      if (result.type == TOTAL_TEAM) {
        getline(ss, result.s1, '"'); // Skip to the quote
        getline(ss, result.s1, '"'); // Extract the team name
      } else {
        ss.ignore(256, ' ');
        getline(ss, result.s1); // Extract the player name directly
      }
      break;
    case 'M':                     // Mean
      ss >> temp >> temp >> temp; // Skip "goals per game"
      ss >> temp;                 // Skip "for" or "by"
      result.type = (temp[0] == 'f') ? MEAN_TEAM : MEAN_PLAYER;
      if (result.type == MEAN_TEAM) {
        getline(ss, result.s1, '"'); // Skip to the quote
        getline(ss, result.s1, '"'); // Extract the team name
      } else {
        ss.ignore(256, ' ');
        getline(ss, result.s1); // Extract the player name directly
      }
      break;
    case 'G':     // Goals
      ss >> temp; // Skip "on"
      ss >> temp;
      if (temp[0] == 'm') { // "minute"
        result.type = GOALS_MINUTE;
        ss >> result.t1;
      } else { // "first" or "last"
        result.type = (temp[0] == 'f') ? GOALS_FIRST : GOALS_LAST;
        ss >> result.t1;
        ss >> temp; // skip "minutes"
      }
      ss >> temp; // Skip "by"
      ss.get();   // Skip space
      getline(ss, result.s1);
      break;
    case 'S':             // Score
      ss >> temp >> temp; // Skip "opens by"
      ss.ignore(256, ' ');
      if (ss.peek() == '"') { // Team name is quoted
        result.type = SCORE_TEAM;
        getline(ss, result.s1, '"'); // Skip to the quote
        getline(ss, result.s1, '"'); // Extract the team name
      } else {
        result.type = SCORE_PLAYER;
        getline(ss, result.s1); // Extract the player name directly
      }
      break;
    }
  }

  return result;
}

struct PlInfo {
  string pl_name;
  int minute;
};

PlInfo parse_plinfo(istream &in) {
  string pl_name;
  int minute;
  string s;
  pl_name.reserve(30);
  while (true) {
    in >> s;
    if (s.back() == '\'') {
      s.pop_back();
      minute = stoi(s);
      break;
    }
    if (!pl_name.empty()) {
      pl_name.push_back(' ');
    }
    pl_name += s;
  }
  in.ignore(numeric_limits<streamsize>::max(), '\n');
  return {pl_name, minute};
}

void solve(istream &in, std::ostream &out) {
  unordered_map<string, InfoTeam> teams;
  unordered_map<string, InfoPlayer> players;
  unordered_map<string, size_t> open_team;
  unordered_map<string, size_t> open_player;
  unordered_map<string, string> pl_to_team;
  auto it = teams.find("sdf");

  while (in) {
    auto line_info = parse_line(in);
    if (line_info.type == UNKNOWN)
      break;
    if (line_info.type == MATCH_INFO) {
      auto &team1 = teams[line_info.s1];
      auto &team2 = teams[line_info.s2];
      team1.matches++;
      team1.total += line_info.t1;
      team2.matches++;
      team2.total += line_info.t2;
      string_view oteam;
      string oplayer;
      size_t min_minute = 95;
      for (size_t k = 0; k < 2; k++) {
        string_view cur_team = k == 0 ? line_info.s1 : line_info.s2;
        size_t iters = k == 0 ? line_info.t1 : line_info.t2;
        for (size_t i = 0; i < iters; i++) {
          auto pl_info = parse_plinfo(in);
          auto &pl = players[pl_info.pl_name];
          pl.total_goals++;
          pl.goals[pl_info.minute]++;
          pl_to_team.insert({pl_info.pl_name, cur_team.data()});
          if (pl_info.minute < min_minute) {
            oteam = cur_team;
            oplayer = pl_info.pl_name;
            min_minute = pl_info.minute;
          }
        }
      }
      if (line_info.t1 + line_info.t2 != 0) {
        open_team[oteam.data()]++;
        open_player[oplayer]++;
      }
    } else if (line_info.type == TOTAL_TEAM) {
      MPRINT(teams, line_info.s1, total, 0);
    } else if (line_info.type == TOTAL_PLAYER) {
      MPRINT(players, line_info.s1, total_goals, 0);
    } else if (line_info.type == MEAN_TEAM) {
      out << static_cast<double>(teams[line_info.s1].total) /
                 teams[line_info.s1].matches
          << '\n';
    } else if (line_info.type == MEAN_PLAYER) {
      auto totam_matches = teams[pl_to_team[line_info.s1]].matches;
      out << static_cast<double>(players[line_info.s1].total_goals) /
                 totam_matches
          << '\n';
    } else if (line_info.type == GOALS_MINUTE) {
      MPRINT(players, line_info.s1, goals[line_info.t1], 0);
    } else if (line_info.type == GOALS_FIRST) {
      auto &arr = players[line_info.s1].goals;
      auto res = accumulate(arr, arr + line_info.t1 + 1, 0);
      out << res << '\n';
    } else if (line_info.type == GOALS_LAST) {
      auto &arr = players[line_info.s1].goals;
      auto res = accumulate(arr + (91 - line_info.t1), arr + 91, 0);
      out << res << '\n';
    } else if (line_info.type == SCORE_TEAM) {
      auto it = open_team.find(line_info.s1);
      if (it == open_team.end()) {
        out << 0 << '\n';
      } else {
        out << open_team[line_info.s1] << '\n';
      }
    } else if (line_info.type == SCORE_PLAYER) {
      auto it = open_player.find(line_info.s1);
      if (it == open_player.end()) {
        out << 0 << '\n';
      } else {
        out << open_player[line_info.s1] << '\n';
      }
    }
  }
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // ifstream in("03");
  // solve(in, cout);
  solve(cin, cout);
  // test();
}

void test() {
  vector<string> inputs{
      "\"Juventus\" - \"Milan\" 3:1 Inzaghi 45' Del Piero 67' Del Piero 90' "
      "Shevchenko 34' Total goals for \"Juventus\" Total goals by Pagliuca "
      "Mean goals per game by Inzaghi \"Juventus\" - \"Lazio\" 0:0 Mean goals "
      "per game by Inzaghi Mean goals per game by "
      "Shevchenko Score opens by Inzaghi ",
      "Total goals by Arshavin "};
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
