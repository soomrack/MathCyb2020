//
// Created by Brave on 28.09.2020.
//

#ifndef TEST_BLOCK_H
#define TEST_BLOCK_H

#include <cstdint>
#include <iostream>

using namespace std;

class Block {
private:
    int index;
    int nonce; // don't understand for what
    time_t timestamp; // time when block was created
    string data; //  data contained in block
    string self_hash; // hash of this block
    string CalculateHash() const;
    ~Block(); // destructor

public:
    string prev_hash; // hash of previous block
    string GetHash();
    Block(); // class constructor
    Block(int index, const string &DataIn);


};


#endif //TEST_BLOCK_H
