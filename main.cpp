#include <iostream>
#include <vector>
#include <algorithm>

#include "blockchain.h"

using namespace std;

int main()
{
    auto *block_chain = new Blockchain();

    auto *first = new Block( 0, 0, std::string( "This is first block" ));
    block_chain->push( *first );

    auto *second = new Block( 0, first->getHash(), std::string( "This is second block" ));
    block_chain->push( *second );

    auto *third = new Block( 0, second->getHash(), std::string( "This is third block" ));
    block_chain->push( *third );

    auto *fourth = new Block( 0, third->getHash(), std::string( "This is fourth block" ));
    block_chain->push( *fourth );

    auto *fifth = new Block( 0, fourth->getHash(), std::string( "This is fifth block" ));
    block_chain->push( *fifth );

    block_chain->printLastMessages(3 );







    return 0;
}