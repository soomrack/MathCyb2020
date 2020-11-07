#include <iostream>
#include <ctime>
#include <string>
#include <memory>
#include "Block.h"

using namespace std;

Block::Block(const string &data, const uint64_t nounce, const uint64_t prev_hash)
        : timestamp(), data(data), nounce(nounce), prev_hash(prev_hash) {
    time(&this->timestamp);
    index = 0;
}

Block::Block(const string &data, const uint64_t nounce, const uint64_t prev_hash,
             const uint64_t timestamp): timestamp(timestamp), data(data), nounce(nounce),
                                        prev_hash(prev_hash) {
    index = 0;
}

uint64_t Block::computeHash() const {
    hash<string> hasher;
    string block_info = to_string(timestamp) + to_string(nounce) +
                        to_string(prev_hash) + data;
    return hasher(block_info);
}

bool compareBlocks(const Block &block1, const Block &block2) {
    if (block1.computeHash() == block2.computeHash())
        return true;
    return false;
}
