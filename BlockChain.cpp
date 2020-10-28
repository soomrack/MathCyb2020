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

int BlockChain::get_length() {
    return Chain.size();
}

// Synchronization

int send_length(string address, int length);
 
int send_block(string address, Block block, int block_number);

int send_success(string address);

int load_data(string address);

// Нужна функция для вывода последнего совпадающего блока в двух блокчейнах. 
// Для этого нужно получить эти два блокчейна. Также нужна проверять хэш или 
