#include "block.h"

#include <boost/functional/hash.hpp>

Block::Block() {}

Block::Block ( const std::string message ) : message( message )
{
    timestamp = boost::posix_time::second_clock::universal_time();
}

Block::Block ( const uint64_t nounce, const std::size_t hash, const std::string message ) :
               nounce( nounce ), hash( hash ), message( message )
{
    timestamp = boost::posix_time::second_clock::universal_time();
}

Block::Block ( const uint64_t nounce, const boost::posix_time::ptime timestamp,
               const std::size_t hash, const std::string message ) :
               nounce( nounce ), timestamp( timestamp ), hash( hash ), message( message )
{

}

Block::Block( const Block &block ) : nounce( block.nounce ), timestamp( block.timestamp ),
              hash( block.hash ), message( block.message )
{

}

Block::~Block()
{

}

std::size_t getHash( Block  &block )
{
    std::string input = boost::lexical_cast<std::string>( block.nounce ) +
                        boost::posix_time::to_iso_string( block.timestamp ) +
                        boost::lexical_cast<std::string>( block.hash ) +
                        block.message;

    return boost::hash_value( input );
}