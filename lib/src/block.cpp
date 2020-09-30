#include "block.h"

#include "openssl/sha.h"

Block::Block() {}

Block::Block ( const uint64_t nounce, const std::string hash, const std::string message ) :
    nounce( nounce ), hash( hash ), message( message )
{
    timestamp = boost::posix_time::second_clock::universal_time();
}

Block::Block ( const uint64_t nounce, const boost::posix_time::ptime timestamp, const std::string hash, const std::string message ) :
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
    std::string data = std::to_string( nounce ) +
            boost::posix_time::to_iso_string( timestamp ) + hash + message;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, data.c_str(), data.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for( int i = 0; i < SHA256_DIGEST_LENGTH; i++ )
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << ( int )hash[i];
    }
    return ss.str();
}