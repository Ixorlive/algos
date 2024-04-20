#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class SqrtDecomposition {
public:
  explicit SqrtDecomposition(const std::vector<int> &array);
  void Insert(int index, int value);
  void Erase(int index);
  int CountLessOrEqual(int left, int right, int value) const;
  void PrintBlocks(bool sorted = false) const;

private:
  size_t size_;
  size_t block_size_ = 300;
  std::vector<std::vector<int>> blocks_;
  std::vector<std::vector<int>> sorted_blocks_;
  size_t GetBlockIndex(int index) const;
  size_t GetIndexInBlock(int index) const;
  void SplitBlock(size_t block_index);
  bool NeedTotalRealloc() const;
  void TotalRealloc();
};

SqrtDecomposition::SqrtDecomposition(const std::vector<int> &array) {
  size_ = array.size();
  int blocks_count_ = (size_ + block_size_ - 1) / block_size_;
  blocks_.resize(blocks_count_);
  sorted_blocks_.resize(blocks_count_);
  for (size_t i = 0; i < size_; ++i) {
    blocks_[i / block_size_].push_back(array[i]);
  }
  for (int i = 0; i < blocks_count_; ++i) {
    sorted_blocks_[i] = blocks_[i];
    std::sort(sorted_blocks_[i].begin(), sorted_blocks_[i].end());
  }
}

size_t SqrtDecomposition::GetBlockIndex(int index) const {
  int seen_elems = 0;
  size_t block_index = 0;
  for (auto const &block : blocks_) {
    seen_elems += block.size();
    if (seen_elems > index) {
      break;
    }
    ++block_index;
  }
  return block_index;
}

size_t SqrtDecomposition::GetIndexInBlock(int index) const {
  int seen_elems = 0;
  int index_in_block = 0;
  for (auto const &block : blocks_) {
    seen_elems += block.size();
    if (seen_elems > index) {
      index_in_block = block.size() - (seen_elems - index);
      break;
    }
  }
  return index_in_block;
}

void SqrtDecomposition::Insert(int index, int value) {
  size_t block_index = GetBlockIndex(index);
  size_t index_in_block = GetIndexInBlock(index);
  if (block_index >= blocks_.size()) {
    blocks_.push_back({});
    sorted_blocks_.push_back({});
  }

  blocks_[block_index].insert(blocks_[block_index].begin() + index_in_block,
                              value);
  sorted_blocks_[block_index].insert(
      std::upper_bound(sorted_blocks_[block_index].begin(),
                       sorted_blocks_[block_index].end(), value),
      value);
  size_++;

  if (blocks_[block_index].size() > 2 * block_size_) {
    SplitBlock(block_index);
  }

  if (NeedTotalRealloc()) {
    TotalRealloc();
  }
}

void SqrtDecomposition::SplitBlock(size_t block_index) {
  std::cerr << "Splitting block " << block_index << std::endl;

  size_t new_block_index = block_index + 1;
  blocks_.emplace(blocks_.begin() + new_block_index,
                  blocks_[block_index].begin() + block_size_,
                  blocks_[block_index].end());

  blocks_[block_index].erase(blocks_[block_index].begin() + block_size_,
                             blocks_[block_index].end());

  sorted_blocks_[block_index] = blocks_[block_index];
  std::sort(sorted_blocks_[block_index].begin(),
            sorted_blocks_[block_index].end());

  sorted_blocks_.emplace(sorted_blocks_.begin() + new_block_index,
                         blocks_[new_block_index].begin(),
                         blocks_[new_block_index].end());
  std::sort(sorted_blocks_[new_block_index].begin(),
            sorted_blocks_[new_block_index].end());
}

void SqrtDecomposition::Erase(int index) {
  size_t block_index = GetBlockIndex(index);
  size_t index_in_block = GetIndexInBlock(index);

  int value = blocks_[block_index][index_in_block];
  blocks_[block_index].erase(blocks_[block_index].begin() + index_in_block);
  sorted_blocks_[block_index].erase(
      std::lower_bound(sorted_blocks_[block_index].begin(),
                       sorted_blocks_[block_index].end(), value));
  size_--;

  if (NeedTotalRealloc()) {
    TotalRealloc();
  }
}

bool SqrtDecomposition::NeedTotalRealloc() const {
  return blocks_.size() > 2 * block_size_ || blocks_.size() < block_size_ / 4;
}

void SqrtDecomposition::TotalRealloc() {
  std::vector<int> new_array;
  for (auto &block : blocks_) {
    new_array.insert(new_array.end(), block.begin(), block.end());
  }
  blocks_.clear();
  sorted_blocks_.clear();
  size_ = new_array.size();
  int blocks_count_ = (size_ + block_size_ - 1) / block_size_;
  blocks_.resize(blocks_count_);
  sorted_blocks_.resize(blocks_count_);
  for (size_t i = 0; i < size_; ++i) {
    blocks_[i / block_size_].push_back(new_array[i]);
  }
  for (int i = 0; i < blocks_count_; ++i) {
    sorted_blocks_[i] = blocks_[i];
    std::sort(sorted_blocks_[i].begin(), sorted_blocks_[i].end());
  }
}

int SqrtDecomposition::CountLessOrEqual(int left, int right, int value) const {
  size_t left_block_index = GetBlockIndex(left);
  size_t left_index_in_block = GetIndexInBlock(left);
  size_t right_block_index = GetBlockIndex(right);
  size_t right_index_in_block = GetIndexInBlock(right);

  int result = 0;
  // if left and right are in the same block
  if (left_block_index == right_block_index) {
    for (size_t i = left_index_in_block; i <= right_index_in_block; ++i) {
      if (blocks_[left_block_index][i] <= value) {
        ++result;
      }
    }
  } else {
    // count in the left block
    for (size_t i = left_index_in_block; i < blocks_[left_block_index].size();
         ++i) {
      if (blocks_[left_block_index][i] <= value) {
        ++result;
      }
    }
    // count in the blocks between left and right
    for (size_t i = left_block_index + 1; i < right_block_index; ++i) {
      result += std::upper_bound(sorted_blocks_[i].begin(),
                                 sorted_blocks_[i].end(), value) -
                sorted_blocks_[i].begin();
    }
    // count in the right block
    for (size_t i = 0; i <= right_index_in_block; ++i) {
      if (blocks_[right_block_index][i] <= value) {
        ++result;
      }
    }
  }
  return result;
}

std::vector<int> ReadArray() {
  size_t size;
  std::cin >> size;
  std::vector<int> array(size);
  for (size_t i = 0; i < size; ++i) {
    std::cin >> array[i];
  }
  return array;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  std::vector<int> array = ReadArray();
  SqrtDecomposition decomposition(array);
  while (std::cin) {
    std::string query_type;
    std::cin >> query_type;
    if (query_type == "+") {
      int index, value;
      std::cin >> index >> value;
      decomposition.Insert(index, value);
    } else if (query_type == "-") {
      int index;
      std::cin >> index;
      decomposition.Erase(index);
    } else if (query_type == "?") {
      int left, right, value;
      std::cin >> left >> right >> value;
      std::cout << decomposition.CountLessOrEqual(left, right, value)
                << std::endl;
    }
  }

  return 0;
}
