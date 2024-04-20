#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

namespace std {
template <> struct hash<pair<int, int>> {
  size_t operator()(const pair<int, int> &p) const {
    return hash<int>()(p.first) ^ hash<int>()(p.second);
  }
};
} // namespace std

const int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
const int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

bool inside_board(int x, int y) { return x >= 0 && x < 8 && y >= 0 && y < 8; }

vector<pair<int, int>> get_valid_knight_moves(int x, int y) {
  vector<pair<int, int>> moves;
  for (int i = 0; i < 8; i++) {
    int new_x = x + dx[i];
    int new_y = y + dy[i];
    if (inside_board(new_x, new_y)) {
      moves.emplace_back(new_x, new_y);
    }
  }
  return moves;
}

pair<int, int> square_to_coord(string square) {
  int x = square[0] - 'a';
  int y = square[1] - '1';
  return {x, y};
}

string coord_to_square(int x, int y) {
  string square;
  square += char('a' + x);
  square += char('1' + y);
  return square;
}

vector<string> shortest_knight_path(string start, string end) {
  auto start_coord = square_to_coord(start);
  auto end_coord = square_to_coord(end);

  queue<pair<int, int>> q;
  q.emplace(start_coord);
  set<pair<int, int>> visited;

  unordered_map<pair<int, int>, pair<int, int>> predecessor;

  while (!q.empty()) {
    auto current = q.front();
    q.pop();

    if (current == end_coord) {
      break;
    }

    visited.insert(current);

    auto moves = get_valid_knight_moves(current.first, current.second);

    for (auto move : moves) {
      if (!visited.count(move)) {
        q.emplace(move);
        predecessor[move] = current;
      }
    }
  }

  vector<string> path;
  auto current = end_coord;
  while (current != start_coord) {
    path.emplace_back(coord_to_square(current.first, current.second));
    current = predecessor[current];
  }
  path.emplace_back(start);

  return path;
}

int main() {
  string start, end;
  cin >> start >> end;
  auto path = shortest_knight_path(start, end);
  std::reverse(path.begin(), path.end());
  for (auto square : path) {
    cout << square << "\n";
  }
  cout << endl;
  return 0;
}
