//
// Created by Sergey on 16.09.2020.
//

#ifndef MATHCYB2020_BLOCKCHAIN_H
#define MATHCYB2020_BLOCKCHAIN_H


#include "Block.h"

#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Blockchain {
public:
    Blockchain();

    void addBlock(Block block);

    vector<Block> chain;
};


#endif //MATHCYB2020_BLOCKCHAIN_H
