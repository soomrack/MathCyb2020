#include "Block.h"
#include "Blockchain.h"

using namespace std;

int main() {
    BlockChain chain1 = BlockChain();
    BlockChain chain2 = BlockChain();
    chain1.loadFromFile("chain1.txt");
    chain2.loadFromFile("chain2.txt");
    chain1.printLastData(3);
    chain2.printLastData(2);
    chain1.sendLength(chain2);
    chain1.printLastData(3);
    chain2.printLastData(3);
    return 0;
}