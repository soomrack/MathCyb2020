#include "block.h"

string   Block::get_message(){return message;}
string   Block::get_name(){ return name;}
uint64_t Block::get_nonce(){ return nonce;}
uint64_t Block::get_hash(){return hash ? hash : 0;}
time_t   Block::get_time_stamp(){ return time_stamp;}
void Block::insert_hash(int block_hash) { this->hash = block_hash;}

Block::Block() {this->name = "None"; this->message = "None"; this->hash = 0; this->nonce = 0; this->time_stamp = NULL;}

Block::Block(const string & name, const string & message, uint64_t hash, uint64_t nonce, time_t time_stamp) {
    this->name = name;
    this->message = message;
    this->hash = hash;
    this->nonce = nonce;
    this->time_stamp = time(nullptr);
}

Block::Block(const string &name, const string &message, uint64_t nonce, time_t time_stamp) {
    this->name = name;
    this->message = message;
    this->nonce = nonce;
    this->time_stamp = time(nullptr);
}

ostream& operator<<(ostream &out, const Block &block) {
    out <<"name: "      << block.name       << endl;
    out <<"message: "   << block.message    << endl;
    out <<"hash: "      << block.hash       << endl;
    out <<"nonce: "     << block.nonce      << endl;
    out <<"time_stamp: "<< block.time_stamp << endl;
    out <<"\n";
    return out;
}

/*
size_t getHash( Block  &block )
{
    SHA256 sha256;
    string str = sha256(to_string(block.get_nonce()) + block.get_message() + to_string(block.get_time_stamp()));
    char* string1 = new char[str.length() + 1];
    strcpy(string1, str.c_str());
    uint64_t val = strtoll(string1, nullptr, 16);
    delete [] string1;

    return val;
}
*/



