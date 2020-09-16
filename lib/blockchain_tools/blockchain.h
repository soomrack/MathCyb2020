/// @file blockchain.h
/// @brief описание блокчейна

#ifndef MATHCYB2020_BLOCKCHAIN_H
#define MATHCYB2020_BLOCKCHAIN_H

#include "block.h"

#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Blockchain
{
public:
    Blockchain();
    vector<Block> chain;
    void addBlock(Block block);
};

#endif //MATHCYB2020_BLOCKCHAIN_H
