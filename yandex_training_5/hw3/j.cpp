#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

int n, k;

constexpr int MAX_DEVS = 101;

struct dev {
  int id;
  set<int> todown;
  int priors[MAX_DEVS]{0};
  size_t downloaded() const { return k - todown.size(); }
};

struct accepted {
  int dev_a;
  int dev_b;
  int part_id;
};

dev devs[MAX_DEVS + 1];

void solve(istream &in, std::ostream &out) {
  in >> n >> k;
  int cur_timeline = 1;
  unordered_map<int, set<int>> parts;
  // init
  for (size_t i = 0; i < k; i++) {
    parts[i].insert(0);
  }
  devs[0].id = 0;
  for (size_t i = 1; i < n; i++) {
    devs[i].id = i;
    for (size_t j = 0; j < k; j++) {
      devs[i].todown.insert(j);
    }
  }
  int res[101]{0};
  accepted req_accepted[MAX_DEVS];
  unordered_map<int, vector<pair<int, int>>> requests;
  while (true) {
    bool stop = true;
    // cout << cur_timeline << "
    // ==============================================\n"; mame requests
    for (size_t i = 1; i < n; i++) {
      if (devs[i].downloaded() == k) {
        if (res[i] == 0) {
          res[i] = cur_timeline - 1;
        }
        continue;
      }
      stop = false;
      // find part to download
      set<int> *avaibles_devs = nullptr;
      int part_id = -1;
      for (int part_id_to_download : devs[i].todown) {
        if (part_id == -1 ||
            parts[part_id_to_download].size() < avaibles_devs->size()) {
          avaibles_devs = &parts[part_id_to_download];
          part_id = part_id_to_download;
        }
      }
      int min_downloaded = 100500;
      int dev_id = -1;
      for (int dev_with_avaibl_part : *avaibles_devs) {
        if (dev_id == -1 ||
            devs[dev_with_avaibl_part].downloaded() < min_downloaded) {
          min_downloaded = devs[dev_with_avaibl_part].downloaded();
          dev_id = dev_with_avaibl_part;
        }
      }
      requests[dev_id].push_back({i, part_id});
    }
    if (stop)
      break;
    // accespt requests
    int q = 0;
    for (auto &[dev_a, req_devs] : requests) {
      int max_prior = -1;
      int min_downloaded_parts = 100500;
      pair<int, int> dev_part = {-1, -1};
      for (auto &[dev_b, part_id] : req_devs) {
        if (dev_part.first == -1) {
          max_prior = devs[dev_a].priors[dev_b];
          min_downloaded_parts = devs[dev_b].downloaded();
          dev_part = {dev_b, part_id};
        } else if (max_prior < devs[dev_a].priors[dev_b]) {
          max_prior = devs[dev_a].priors[dev_b];
          min_downloaded_parts = devs[dev_b].downloaded();
          dev_part = {dev_b, part_id};
        } else if (max_prior == devs[dev_a].priors[dev_b] &&
                   devs[dev_b].downloaded() < min_downloaded_parts) {
          min_downloaded_parts = devs[dev_b].downloaded();
          dev_part = {dev_b, part_id};
        }
      }
      req_accepted[q++] = {dev_a, dev_part.first, dev_part.second};
    }
    for (size_t i = 0; i < q; i++) {
      const auto &acc = req_accepted[i];
      // cout << acc.dev_a << "->" << acc.dev_b << ": " << acc.part_id << '\n';
      parts[acc.part_id].insert(acc.dev_b);
      devs[acc.dev_b].todown.erase(acc.part_id);
      devs[acc.dev_b].priors[acc.dev_a]++;
    }
    requests.clear();
    ++cur_timeline;
  }
  for (size_t i = 1; i < n; i++) {
    out << res[i] << ' ';
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
  vector<string> inputs{"3 2", "4 3", "4 4", "3 10"};
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
