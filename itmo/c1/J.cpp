#include <cstdint>
#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using Time = std::uint16_t;
using block_id = std::uint16_t;
using Block = std::pair<Time, block_id>;
#define MAX_BLOCKS 30000 // count blocks
#define T 600            // lifetime of block

template <typename PriorQ>
bool free_blocks_time_up(std::set<Block> &blocks,
                         std::vector<Time> &block_is_free, PriorQ &free_blocks,
                         Time time_now, block_id b_id) {
  bool block_time_up = false;
  auto first_it = blocks.begin();
  while (first_it != blocks.end() && first_it->first + T <= time_now) {
    auto block_id = first_it->second;
    free_blocks.push(block_id);
    blocks.erase(blocks.begin());
    block_is_free[block_id] = 0;
    if (block_id == b_id) {
      block_time_up = true;
    }
    first_it = blocks.begin();
  }
  return block_time_up;
}

void ManageMemory(std::istream &in, std::ostream &out) {
  // std::priority_queue<Block> blocks;
  std::set<Block> blocks;
  std::vector<Time> block_is_free(MAX_BLOCKS + 1, 0);
  std::priority_queue<block_id, std::vector<block_id>, std::greater<>>
      free_blocks;
  for (size_t i = 1; i < MAX_BLOCKS + 1; ++i) {
    free_blocks.push(i);
  }
  bool first = true;
  while (!in.eof()) {
    Time time_now;
    in >> time_now;
    if (in.eof())
      return;
    char op;
    in >> op;
    if (op == '+') {
      if (!blocks.empty()) {
        free_blocks_time_up(blocks, block_is_free, free_blocks, time_now, 0);
      }
      auto free_block = free_blocks.top();
      free_blocks.pop();
      out << (first ? "" : "\n") << free_block;
      block_is_free[free_block] = time_now;
      // blocks.push({time_now, free_block});
      blocks.insert({time_now, free_block});
    } else {
      block_id b_id;
      in >> b_id;
      if (block_is_free[b_id] == 0) {
        out << (first ? "" : "\n") << '-';
      } else {
        auto block_time_up = free_blocks_time_up(blocks, block_is_free,
                                                 free_blocks, time_now, b_id);
        if (!block_time_up) {
          out << '\n' << '+';
          auto it = blocks.find({block_is_free[b_id], b_id});
          blocks.erase(it);
          blocks.insert({time_now, b_id});
          block_is_free[b_id] = time_now;
        } else {
          out << '\n' << '-';
        }
      }
    }
    first = false;
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // Test();
  ManageMemory(std::cin, std::cout);
}
