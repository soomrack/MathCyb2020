#include "block.h"

string   Block::get_message(){ return message; }
string   Block::get_name(){ return name; }
string Block::get_nonce(){ return nonce; }
string Block::get_hash(){ return hash; }
time_point   Block::get_time_stamp(){ return time_stamp; }

void Block::insert_hash(int block_hash) { this->hash = block_hash; }

Block::Block() {
  this->name = "";
  this->message = "";
  this->hash = "";
  this->nonce = "";
  this->time_stamp = time_point();
}

Block::Block(const string & name, const string & message, uint64_t hash, string nonce, time_point time_stamp) {
  this->name = name;
  this->message = message;
  this->hash = hash;
  this->nonce = nonce;
  this->time_stamp = time_stamp;
}

Block::Block(const string &name, const string &message, string nonce, const Block &block) {
  this->name = name;
  this->message = message;
  this->nonce = nonce;
  this->time_stamp = chrono::system_clock::now();
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256_CTX sha256;
  string to_hash = name + message + nonce + block.hash;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256,to_hash.c_str(), to_hash.size());
  SHA256_Final(hash, &sha256);
  stringstream ss;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    ss << hex << setw(2) << setfill('0') << (int)hash[i];
  }
  this->hash = ss.str();
}

ostream& operator<<(ostream &out, const Block &block) {
  out <<"name: "      << block.name       << endl;
  out <<"message: "   << block.message    << endl;
  out <<"hash: "      << block.hash       << endl;
  out <<"nonce: "     << block.nonce      << endl;
  out <<"time_stamp: "<< chrono::system_clock::to_time_t(block.time_stamp) << endl;
  out <<"\n";
  return out;
}
