//
// Created by Brave on 28.09.2020.
//

#include "Block.h"
#include <sha256.h>

Block::Block(int index, const string &DataIn) : {
    nonce = -1;
    timestamp = time(nullptr);
}

string Block::GetHash() {
    return self_hash;
}

//
// void Block::MiningBlock(uint32_t Difficulty) {
//    char cstr[Difficulty + 1];
//    for (uint32_t i = 0; i < Difficulty; ++i) {
//        cstr[i] = ‘0’;
//    }
//    cstr[Difficulty] = ‘\0’;
//    string str(cstr);
//    do {
//        nonce++;
//        self_hash = CalculateHash();
//    } while (self_hash.substr(0, Difficulty) != str);
//    cout << “Block mined: “ << self_hash << endl;
//}

inline string Block::CalculateHash() const {
    stringstream ss;
    ss << index << timestamp << data << nonce << prev_hash;
    return sha256(ss.str());
}