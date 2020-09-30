#include <iostream>
#include <vector>

#include "blockchain.h"

using namespace std;

int main()
{
    auto *block_chain = new Blockchain();

    auto *first = new Block( 0, "", "This is first block");
    block_chain->push( *first );

    auto *second = new Block( 0, first->getHash(), "This is second block");
    block_chain->push( *second );

    auto *third = new Block( 0, second->getHash(), "This is third block");
    block_chain->push( *third );

    auto *fourth = new Block( 0, third->getHash(), "This is fourth block");
    block_chain->push( *fourth );

    auto *fifth = new Block( 0, fourth->getHash(), "This is fifth block");
    block_chain->push( *fifth );

    block_chain->saveToFile( "temp.txt" );
    block_chain->loadFromFile("temp.txt" );

    block_chain->printLastMessages(5);

    return 0;
}