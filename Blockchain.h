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
    int n_same = len();     // номер крайнего совпадающего блока
    int send_length(string address);
    bool check_length(string address);
    bool check_same(Block block);       // проверка совпадения последних блоков
    int send_block(string address, int i);
    int send_success(string address);
    int sync(string alice_len_address, string my_len_address,
            string alice_block_address, string my_block_address,
             string alice_success_address, string my_success_address);


};


#endif //BLOCKCHAIN_BLOCKCHAIN_H
