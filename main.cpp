#include <iostream>

#include "lib/blockchain_tools/blockchain.h"

using namespace std;

int main() {
    auto *block_chain = new Blockchain();

    cout << "Mining block 1..." << endl;
    block_chain->addBlock(Block("block 1 Data" ) );

    cout << "Mining block 2..." << endl;
    block_chain->addBlock(Block("block 2 Data" ) );

    cout << "Mining block 3..." << endl;
    block_chain->addBlock(Block("block 3 Data" ) );

    return 0;
}