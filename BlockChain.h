//
// Created by Brave on 28.09.2020.
//

#ifndef TEST_BLOCKCHAIN_H
#define TEST_BLOCKCHAIN_H

#include <cstdint>
#include <list>
#include “Block.h”

using namespace std;

class BlockChain {
private:
    list<Block> Chain;
    Block GetLastBlock() const;
    uint32_t Difficulty; // Difficulty Target for mining

public:
    BlockChain();
    void AddBlock(Block B_New);
    int get_length();
	Block GetBlock(int index);

};


#endif //TEST_BLOCKCHAIN_H
