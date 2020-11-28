#include <iostream>
#include <string>
#include <tuple>
#include <ctime>
#include <cstdint>
#include <openssl/sha.h>

using namespace std;

struct Block {
private:
  string name;
  string message;
  uint64_t nonce{};
  uint64_t hash{};
  time_t time_stamp{};

  
public:
  Block();
  ~Block() = default;
  explicit Block(const string& name, const string& message, uint64_t hash, uint64_t nonce, time_t time_stamp);
  explicit Block(const string& name, const string& message, uint64_t nonce, time_t time_stamp);
  
  string get_message();
  string get_name();
  uint64_t get_nonce();
  uint64_t get_hash();
  time_t get_time_stamp();
  tuple<string,string,uint64_t,uint64_t,time_t> get_all(){return make_tuple(message,name,nonce,hash,time_stamp);}
  
  void insert_hash(int block_hash);

  friend ostream& operator<<(ostream &out,const Block &block);

};
