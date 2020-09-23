//
// Created by belyn on 09.09.2020.
//

#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H

#include<iostream>
#include<string>
#include<cstdint>

using namespace std;

class Block {
private:
    string Name;
    string Data;
    time_t TimeStamp;

public:
    uint64_t Nounce;
    uint64_t PrevHash;
    Block();
    Block(string Name, string Dt, uint64_t Nnc, uint64_t PrHsh);
    ~Block();
    friend ostream& operator<< (ostream &out, const Block &block);

};


#endif //BLOCKCHAIN_BLOCK_H
