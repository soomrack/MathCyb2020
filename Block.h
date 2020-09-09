//
// Created by belyn on 09.09.2020.
//

#ifndef BLOCKCHAIN_BLOCK_H
#define BLOCKCHAIN_BLOCK_H

#include<iostream>
#include<string>
using namespace std;

class Block {
private:
    string Name;
    string Data;
    int Nounce;
    time_t TimeStamp;
    string PrevHash;
public:
    Block(string Name, string Dt, int Nnc, string PrHsh);
    friend ostream& operator<< (ostream &out, const Block &block);

};


#endif //BLOCKCHAIN_BLOCK_H
