//
// Created by belyn on 16.09.2020.
//

#include "Blockchain.h"
#include <stdexcept>

using namespace std;

Blockchain::Blockchain() {vector<Block> chain1; chain = chain1;}

Blockchain::Blockchain(Block block)
{
    vector <Block> chain1;
    chain = chain1;
    chain.push_back(block);
}

Blockchain::Blockchain(Block block, uint64_t M): M(M)
{
    vector <Block> chain1;
    chain = chain1;
    chain.push_back(block);
}
Blockchain::Blockchain(vector<Block> &v):chain(v){};

Blockchain::~Blockchain(){
    chain.clear();
    }


int  Blockchain::len(){return chain.size();}

uint64_t Blockchain::hash(Block block){ // TO DO
    return 33;
}

int Blockchain::add(Block block){
    try
    {
        if(block.PrevHash != hash(pop()))
        {throw -1;}
        if (block.Nounce >= M)
        {throw -2;}

        chain.push_back(block);
    }
    catch(int exc){
        if(exc == -1){cout << "wrong hash"<<endl;}
        if(exc == -2){cout << "no proof of work"<<endl;}
        return exc;
    }
    catch(exception &exc)
    {
        cout<<exc.what()<<endl;
        return -3;
    }
    return 0;
}

// should delete from chain?
Block Blockchain::pop(){
    Block block = chain[chain.size() - 1];
    return block;
}

int Blockchain::print_last_messages(int n) {
    if(n > chain.size())
    {cout<<"wrong index"<<endl; return -1;}
    int last_id = chain.size() - 1;
    for (int i = 0; i < n; ++i){
        cout<< "number: "<< last_id - i << chain[last_id - i]<<endl;
    }
    return n;
}

ostream& operator<<(ostream &out, const Blockchain &chain){
    out<< "chain length = "<< chain.chain.size()<<'\n'<<"blocks: "<<endl;
    for(int i=0; i < chain.chain.size(); ++i){
        out<<chain.chain[i]<<endl;
    }
    return out;
}
