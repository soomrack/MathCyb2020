#include <stdio.h>

#include <ctime.h>
#include <cstdint.h>

#include <list.h>
#include <string.h>


class Block {
private:
  uint64_t nounce;  // Parameter for proof-of-work
  uint64_t hash;  // Hash of previouse block, 0 for the first block
  time_t timestamp;  // Timestamp when block was created
  string message;  // Data stored in one block of blockchain

public:
  Block();
  Block(const string message, const uint64_t nounce, const uint64_t hash);
  Block(const Block &block);

private:
  ~Block();
};


class BlockChain {
private:
  std::list<Block> chain;

public:
  BlockChain();

private:
  ~BlockChain();

public:
  int push(const Block new_tail);  // Add new block to tail of chain
  Block pop();  // Delete tail block from chain and return it

public:
  int save_to_file(const string filename);
  int load_from_file(const string filename);
  
public:
  int print_last_messages(const int n);  // Print to console messages from n tail blocks
                                         // return number of printed messages
}



int main () {
  printf("Success!");
}






