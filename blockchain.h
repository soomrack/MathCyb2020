#include "block.h"
#include <list>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class Blockchain {
private:
  vector<Block> blockchain;

public:
  Blockchain() = default;
  explicit Blockchain(Block &genesis);

  void push(const Block &block);
  void pop();
  Block& back();
  Block& get_block(int index);
  size_t size();
  unsigned int print_last_messages(int n);

  unsigned int save_to_file(const string &file_name); 
  unsigned int load_from_file(const string &file_name);

  Block& operator[](int index);
  friend ostream& operator<<(ostream &out, const Blockchain &chain);

  Blockchain send_data(int index);

  void load_data(Blockchain chain, int index);

  int has_block(Block &block);

};

bool sync(Blockchain &chain1, Blockchain &chain2);
