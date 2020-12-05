#include <iostream>
#include <string>
#include <tuple>
#include <ctime>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <openssl/sha.h>

using namespace std;
using time_point = chrono::time_point<chrono::high_resolution_clock>;


struct Block {
private:
  string name;
  string message;
  string nonce;
  string hash;
  time_point time_stamp;

  
public:
  Block();
  ~Block() = default;
  explicit Block(const string& name, const string& message, string hash, string nonce, time_point time_stamp);
  explicit Block(const string& name, const string& message, string nonce, const Block& block);
  
  string get_message();
  string get_name();
  string get_nonce();
  string get_hash();
  time_point get_time_stamp();
  tuple<string,string,string,string,time_point> get_all(){return make_tuple(message,name,nonce,hash,time_stamp);}
  
  void insert_hash(int block_hash);

  friend ostream& operator<<(ostream &out,const Block &block);

};
