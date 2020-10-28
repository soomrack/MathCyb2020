//
// Created by belyn on 16.09.2020.
//

#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H

#include <vector>
#include <cstdint>
#include "Block.h"

using namespace std;

class Blockchain {
public:
    Blockchain();
    vector<Block> chain;
    uint64_t M = 10; // мощность сети
    Blockchain(Block block);
    Blockchain(Block block, uint64_t M);
    Blockchain(vector<Block> &v);
    ~Blockchain();
    int len();
    int add(Block block);
    uint64_t hash(Block block);
    Block pop();
    int save_to_file(string filename);
    int load_from_file(string filename);
    int print_last_messages(int n);
    friend ostream& operator<< (ostream &out, const Blockchain &chain);

    // синхронизация
    vector<Block> temp_chain;
    int n_same = len();     // номер крайнего совпадающего блок
    int sync(Blockchain &other);


};


#endif //BLOCKCHAIN_BLOCKCHAIN_H
