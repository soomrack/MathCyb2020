#include <iostream>
#include "Block.h"
#include "Block.cpp"
#include "Blockchain.h"
#include "Blockchain.cpp"
#include<string>
using namespace std;

int main() {
    int nounce = 0;
    string phash = "some hash", data = "some data", name = "Alice";
    Block block(name, data, nounce, phash);
    Block new_block("Bob", "data", 1, "hash");
//    cout<<block<<endl;
    Blockchain chain(block);
    chain.add(new_block);
    cout<<chain;
    return 0;
}