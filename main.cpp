#include "block.h"
#include "blockchain.h"


using namespace std;

int main() {


    Block block1("Paul", "Message", 0,1);
    Block block2("Aaron","Message2",getHash(block1),2);
    Block block3("Mike", "Message3",getHash(block2),3);
    Block block4("Fred", "Message4",getHash(block3),4);
    Block block5("Alice","Message5",getHash(block4),5);
    Block block6("Alex", "Message6",getHash(block5),6);

    BlockChain chain1;
    chain1.push(block1);
    chain1.push(block2);
    chain1.push(block3);

    BlockChain chain2;
    chain2.push(block1);
    chain2.push(block2);
    chain2.push(block3);
    chain2.push(block4);
    chain2.push(block5);
    chain2.push(block6);

    if(sync(chain1,chain2))
        cout << "Succeed! " << endl;
    else {
        cout << "Error! " << endl;
        return EXIT_FAILURE;
    }
    cout << chain1 << endl;
    cout << chain2 << endl;


    return EXIT_SUCCESS;
}

