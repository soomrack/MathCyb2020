#include <iostream>
#include <vector>

#include "block.h"
#include "blockchain.h"

using namespace std;

int main()
{
    // генерируем цепь Alice
    auto alice_chain = Blockchain();

    auto *afirst = new Block( 0, 0, "This is a first block of Alice" );
    alice_chain.push( *afirst );

    auto *asecond = new Block( 0, getHash( *afirst ), "This is a second block of Alice" );
    alice_chain.push( *asecond );

    auto *athird = new Block( 0, getHash( *asecond ),"This is a third block of Alice" );
    alice_chain.push( *athird );

    auto *afourth = new Block( 0, getHash( *athird ),"This is a fourth block of Alice" );
    alice_chain.push( *afourth );

    auto *afifth = new Block( 0, getHash( *afourth ),"This is a fifth block of Alice" );
    alice_chain.push( *afifth );

    std::cout << "Alice blockchain: " <<std::endl;
    alice_chain.printLastMessages(5);

    // генерируем цепь bob
    auto bob_chain = Blockchain();

    auto *bfirst = new Block( 0, 0, "This is a first block of Bob" );
    bob_chain.push( *bfirst );

    auto *bsecond = new Block( 0, getHash( *bfirst ), "This is a second block of Bob" );
    bob_chain.push( *bsecond );

    auto *bthird = new Block( 0, getHash( *bsecond ),"This is a third block of Bob" );
    bob_chain.push( *bthird );

    std::cout << "Bob blockchain: " <<std::endl;
    bob_chain.printLastMessages(5);


    synchronize( alice_chain, bob_chain );
    std::cout << "Alice blockchain after synchronization: " <<std::endl;
    alice_chain.printLastMessages(5);
    std::cout << "Bob blockchain after synchronization: " <<std::endl;
    bob_chain.printLastMessages(5);

    return 0;
}