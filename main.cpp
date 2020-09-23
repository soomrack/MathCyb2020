#include <iostream>
#include "Block.h"
#include "Block.cpp"
#include "Blockchain.h"
#include "Blockchain.cpp"
#include<string>
using namespace std;

int main() {
    uint64_t nounce = 0, phash = 33;
    string  data = "some data", name = "Alice";
    Block block(name, data, nounce, phash);
    Block new_block("Bob", "data", 1, 33);
//    cout<<block<<endl;
    Blockchain chain(block);
    chain.add(new_block);
    chain.print_last_messages(2);
//    cout<<chain;
    return 0;
}