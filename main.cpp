#include <iostream>
#include <string>
#include <ctime>

using namespace std;

struct Block
{
      int index;
      time_t timestamp;
      string data;
      string hash;
      string prev_hash;
};

class Blockchain
{
    Block* blocks;

    void make_data()
    {

    }
};

string calc_hash(struct Block some_block)
{
    string hash;
    return hash;
}

int main()
{
    return 0;
}
