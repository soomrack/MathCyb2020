
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
int Blockchain::send_length(string address){
    ofstream output_file;
    output_file.open(address, std::ios_base::trunc);
    if(output_file.fail())
    {
        std::cout<<"unable to send"<<endl;
        return 1;
    }
    output_file << len() << "\n";
    output_file.close();
    return 0;
}

bool Blockchain::check_length(string address){
    ifstream is(address);
    int read_len;
    is >> read_len;
    if (len() >= read_len) return true;
    return false;
}

bool Blockchain::check_same(Block block){
    if(hash(block) == hash(chain[chain.size() - 1])) return true;
    return false;
}

int Blockchain::send_block(string address, int i){
    Block block = chain[i];
    ofstream output_file;
    output_file.open(address, std::ios_base::trunc);
    if(output_file.fail())
    {
        std::cout<<"unable to send"<<endl;
        return 1;
    }
    output_file << block << "\n";
    output_file.close();
    return 0;
}

int Blockchain::send_success(string address){
    ofstream output_file;
    output_file.open(address, std::ios_base::trunc);
    if(output_file.fail())
    {
        std::cout<<"unable to send"<<endl;
        return 1;
    }
    output_file << 0 << "\n";
    output_file.close();
    return 0;
}

// TODO
int Blockchain::sync(string alice_len_address, string my_len_address,
        string alice_block_address, string my_block_address,
        string alice_success_address, string my_success_address){
    send_length(my_len_address);
    if(check_length(alice_len_address))   // моя цепь длиннее - читаем блоки алисы, пока не совпадают,
        // записываем в temp_chain, присоединяем, посылаем алисе success
    {
        while(true){

        }
    }
    // иначе посылаем алисе блоки, она она не пошлет флаг на my_success_address
}