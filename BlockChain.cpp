//
// Created by Brave on 28.09.2020.
//

#include "BlockChain.h"

BlockChain::BlockChain() {
    Chain.emplace_back(Block(0, "Genesis Block"));
    Difficulty = 6;
}

void BlockChain::AddBlock(Block B_New) {
    B_New.prev_hash = GetLastBlock().GetHash();
    B_New.MiningBlock(Difficulty);
    Chain.push_back(B_New);
}

Block BlockChain::GetLastBlock() const{
    return Chain.push_back();
}
