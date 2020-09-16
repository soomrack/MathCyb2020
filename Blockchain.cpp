//
// Created by belyn on 16.09.2020.
//

#include "Blockchain.h"

using namespace std;

Blockchain::Blockchain() {vector<Block> chain1; chain = chain1;}
Blockchain::Blockchain(Block block){
    vector <Block> chain1;
    chain = chain1;
    chain.push_back(block);
}
Blockchain::Blockchain(vector<Block> &v):chain(v){};

int  Blockchain::len(){return chain.size();}

void Blockchain::add(Block block){ // TO DO
    chain.push_back(block);
}

ostream& operator<<(ostream &out, const Blockchain &chain){
    out<< "chain length = "<< chain.chain.size()<<'\n'<<"blocks: "<<endl;
    for(int i=0; i < chain.chain.size(); ++i){
        out<<chain.chain[i]<<endl;
    }
    return out;
}
