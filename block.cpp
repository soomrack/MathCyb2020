#include "block.h"

string   Block::get_message(){return message;}
string   Block::get_name(){ return name;}
uint64_t Block::get_nonce(){ return nonce;}
uint64_t Block::get_hash(){return hash;}
time_t   Block::get_time_stamp(){ return time_stamp;}

Block::Block() {this->name = "None"; this->message = "None"; this->hash = 0; this->nonce = 0; this->time_stamp = NULL;}
Block::Block(const string & name, const string & message, uint64_t hash, uint64_t nounce, time_t time_stamp) {
    this->name = name;
    this->message = message;
    this->hash = hash;
    this->nonce = nounce;
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
