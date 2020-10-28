
#include "Blockchain.h"
#include <stdexcept>
#include<fstream>
#include<iterator>
#include<algorithm>
#include<stdlib.h>
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

    return rand() % 5;
}

int Blockchain::add(Block block){
    // временно закомменчено для тестирования

//    if(block.PrevHash != hash(chain[chain.size() - 1]))
//        {return -1;}
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
    for(const auto &e : chain) output_file << e << "\n";
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

// синхронизация

int Blockchain::sync(Blockchain &other){
    vector<Block> temp;
    Blockchain *big, *small;
    if(len()<other.len()) {small = this; big  = &other;}
    else {big = this; small = &other; };
//    cout<<*small;
//    cout<<*big;
    int i = 1;
    Block last_big = big->chain[big->chain.size() - i];
    while (i <= big->chain.size()){
    for(int j = small->chain.size() - 1; j >= 0; --j)
    {
        if (last_big.PrevHash == small->chain[j].PrevHash) // PrevHash вместо Hash пока не имплементирован hash
        {
            for(int k=small->chain.size() - 1; k != j; --k)
            {
                small->chain.pop_back();
            }
            for(int k = temp.size() - 1; k >= 0; --k)
            {
            small->chain.push_back(temp[k]);
            }
            break;
        }
    }
        temp.push_back(last_big);
        ++i;
        if (i <= big->chain.size() )last_big = big->chain[big->chain.size() - i];
    }
//    cout<<*small;
//    cout<<*big;
    return 0;
}