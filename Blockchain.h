//
// Created by belyn on 16.09.2020.
//

#ifndef BLOCKCHAIN_BLOCKCHAIN_H
#define BLOCKCHAIN_BLOCKCHAIN_H

#include <vector>
#include "Block.h"

using namespace std;

class Blockchain {
private:
    vector<Block> chain;
public:
    Blockchain();
    Blockchain(Block block);
    Blockchain(vector<Block> &v);
    int len();
    void add(Block block);
    friend ostream& operator<< (ostream &out, const Blockchain &chain);

};


#endif //BLOCKCHAIN_BLOCKCHAIN_H
