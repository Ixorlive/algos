#include <algorithm>
#include <bitset>
#include <cstdint>
#include <iostream>
#include <limits>
#include <sstream>
#include <unordered_set>
#include <vector>

using namespace std;
class BloomFilter {
private:
  vector<bool> bitArray;
  hash<string> stdHash;

  size_t customHash(const std::string &s, int p) const {
    size_t hash = 0, p_pow = 1;
    for (char c : s) {
      hash += (std::tolower(c) - 'a' + 1) * p_pow;
      p_pow *= p;
    }
    return hash;
  }

public:
  BloomFilter(size_t size) : bitArray(size) {}
  void add(const std::string &s) {
    size_t hash1 = stdHash(s) % bitArray.size();
    size_t hash2 = customHash(s, 31) % bitArray.size();

    bitArray[hash1] = true;
    bitArray[hash2] = true;
  }
  bool possiblyContains(const std::string &s) const {
    size_t hash1 = stdHash(s) % bitArray.size();
    size_t hash2 = customHash(s, 31) % bitArray.size();
    return bitArray[hash1] && bitArray[hash2];
  }
};
void solve(istream &in, std::ostream &out) {
  int n;
  in >> n;
  string str;
  in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  str.reserve(2001);
  int res = 0;
  BloomFilter filter(1700000);
  for (int i = 0; i < n; i++) {
    std::getline(in, str);
    if (!filter.possiblyContains(str)) {
      res++;
      filter.add(str);
    }
  }
  out << res;
}

void test();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // solve(cin, cout);
  test();
}

void test() {
  vector<string> inputs{
      "8 вк\nрефераты\nвк\nок\nодноклассники\nяндекс\nвконтакте\nок"};
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
