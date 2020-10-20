#include "block.h"

#include "sha256.h"

Block::Block() {}

Block::Block ( const uint64_t nounce, const std::string hash, const std::string message ) :
    nounce( nounce ), hash( hash ), message( message )
{
    timestamp = boost::posix_time::second_clock::universal_time();
}

Block::Block ( const uint64_t nounce, const boost::posix_time::ptime timestamp,
               const std::string hash, const std::string message ) :
        nounce( nounce ), timestamp( timestamp ), hash( hash ), message( message )
{

}

Block::Block( const Block &block ) :
    nounce( block.nounce ), timestamp( block.timestamp ), hash( block.hash ), message( block.message )
{

}

Block::~Block()
{

}

std::string Block::getHash()
{
    std::string input = boost::lexical_cast<std::string>( nounce ) +
                        boost::posix_time::to_iso_string( timestamp ) +
                        hash + message;
    return sha256( input );
}