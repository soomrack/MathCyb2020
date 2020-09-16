/// @file block.h
/// @brief описание блока

#ifndef MATHCYB2020_BLOCK_H
#define MATHCYB2020_BLOCK_H

#include <cstdint>
#include <iostream>
#include <sstream>

using namespace std;

class Block {
public:
    string get;
    Block(const string data);
    string GetHash();
    static void MineBlock(Block lastBlock, string data);

private:
    int difficulty;
    int nonce;
    string data;
    string hash;
    string lastHash;
    time_t timestamp;

    string _CalculateHash() const;
};

#endif //MATHCYB2020_BLOCK_H
