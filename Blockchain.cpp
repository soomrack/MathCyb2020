//
// Created by belyn on 16.09.2020.
//

#include "Blockchain.h"
#include <stdexcept>
#include<fstream>
#include<iterator>
#include<algorithm>

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

uint64_t Blockchain::hash(Block block){ // TODO
    return 33;
}

int Blockchain::add(Block block){
    if(block.PrevHash != hash(chain[chain.size() - 1]))
        {return -1;}
    if (block.Nounce >= M)
        {return -2;}

    chain.push_back(block);
    return 0;
}


Block Blockchain::pop(){
    Block block = chain[chain.size() - 1];
    chain.pop_back();
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

int Blockchain::save_to_file(string filename) {
    ofstream output_file;
    output_file.open(filename, std::ios_base::trunc);
    if(output_file.fail())
        std::cout<<"unable to open the file"<<endl;
//    ostream_iterator<Blockchain> output_iterator(output_file, "\n");
//    copy(chain.begin(), chain.end(), output_iterator);
    for(const auto &e : chain) output_file << e << "\n";
//    output_file<<"hello";
    output_file.close();
    return 0;
}

int Blockchain::load_from_file(string filename) {
    ifstream is(filename);
    istream_iterator<Block> start(is), end;
    vector<Block> chain_(start, end);
    chain = chain_;
    return 0;
}