#include <iostream>
#include "Block.h"
#include "Block.cpp"
#include "Blockchain.h"
#include "Blockchain.cpp"
#include<string>
using namespace std;

int main() {
    uint64_t nounce = 0, phash = 33;
    string  data = "somedata", name = "Alice";
    Block block(name, data, nounce, phash);
    Block new_block("Bob", "data", 1, 33);
//    cout<<block<<endl;
    Blockchain chain(block);
    chain.add(new_block);
//    chain.print_last_messages(2);
    cout<<chain;

    chain.save_to_file("chain.txt");
    chain.pop();
    cout<<chain;
    chain.load_from_file("chain.txt");
    cout<<chain;
    return 0;
}