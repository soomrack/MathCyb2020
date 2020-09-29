#include "block.h"

Block::Block() {}

Block::Block ( const uint64_t nounce, const uint64_t hash, const std::string message ) :
    nounce( nounce ), hash( hash ), message( message )
{
    timestamp = std::time(0);
}

Block::Block ( const uint64_t nounce, const time_t timestamp, const uint64_t hash, const std::string message ) :
        nounce( nounce ), timestamp(timestamp), hash( hash ), message( message )
{

}

Block::Block( const Block &block ) :
    nounce( block.nounce ), timestamp( block.timestamp ), hash( block.hash ), message( block.message )
{

}

Block::~Block()
{

}

uint64_t Block::getHash()
{
    // TODO сделать импелментацию подсчета хэша
    return 25;
}