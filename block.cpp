#include "block.h"
#include <boost/functional/hash.hpp>



string   Block::get_message(){return message;}
string   Block::get_name(){ return name;}
uint64_t Block::get_nonce(){ return nonce;}
uint64_t Block::get_hash(){return hash ? hash : 0;}
boost::posix_time::ptime Block::get_time_stamp(){ return time_stamp;}

void Block::insert_hash(int block_hash) { this->hash = block_hash;}

Block::Block() {
    this->name = "None";
    this->message = "None";
    this->hash = 0; this->nonce = 0;
    this->time_stamp = boost::posix_time::second_clock::universal_time();
}

Block::Block(const string & name, const string & message, uint64_t hash, uint64_t nonce) {

    this->name = name;
    this->message = message;
    this->hash = hash;
    this->nonce = nonce;
    this->time_stamp = boost::posix_time::second_clock::universal_time();
}

Block::Block(const string &name, const string &message, uint64_t nonce, time time_stamp) {

    this->name = name;
    this->message = message;
    this->nonce = nonce;
    this->time_stamp = boost::posix_time::second_clock::universal_time();
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

size_t getHash( Block  &block )
{
    string input = to_string(block.get_nonce() ) +
                        boost::posix_time::to_iso_string( block.get_time_stamp() ) +
                        to_string(block.get_hash() ) +
                        block.get_message();

    return boost::hash_value( input );
}



