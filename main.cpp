#include <iostream>
#include "Block.h"
#include "Block.cpp"
#include "Blockchain.h"
#include "Blockchain.cpp"
#include<string>
using namespace std;

int main() {
    uint64_t nounce = 0, phash = 33;
    string  data = "data", name = "BobAlice";
    Block block(name, data, nounce, phash);
    Block new_block("Bob", "data", 1, 34);
    Block block0("BobAlice", "data", 1, 32);
    Block block1("Bob", "data", 1, 35);
    Block block2("Bob", "data", 1, 36);
    Block block3("Alice", "data", 1, 31);
    Block block4("Alice", "data", 1, 32);
//    cout<<block<<endl;
    Blockchain chain(block0);
    chain.add(block);
    chain.add(new_block);
    chain.add(block1);
    chain.add(block2);
    Blockchain sec_chain(block0);
    sec_chain.add(block);
    sec_chain.add(block3);
    sec_chain.add(block4);
    cout<<chain;
    cout<<sec_chain;
    int i = sec_chain.sync(chain);
    cout<<chain;
    cout<<sec_chain;

////    chain.print_last_messages(2);
//    cout<<chain;
//
//    chain.save_to_file("chain.txt");
//    chain.pop();
//    cout<<chain;
//    chain.load_from_file("chain.txt");
//    cout<<chain;
    return 0;
}