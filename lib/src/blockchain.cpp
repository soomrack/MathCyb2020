#include <algorithm>
#include <iostream>
#include <fstream>

#include "blockchain.h"

Blockchain::Blockchain() {}

Blockchain::~Blockchain() {}

int Blockchain::push( const Block new_tail )
{
    // если добавление завершилось с ошибкой, функция
    // push_back не генерирует исключения и не возвращает код ошибки
    // будем считать успехом увеличение числа элементов на 1
    int size_before_push = chain.size();
    chain.push_back( new_tail );

    int error;
    if ( size_before_push + 1 == chain.size() )
    {
        error = 0;
    }
    else
    {
        error = 1;
    }
    return error;
}

Block Blockchain::pop()
{
    Block old_tail = chain.back();
    chain.pop_back();
    return old_tail;
}

int Blockchain::saveToFile( std::string file_name )
{
    std::ofstream out;
    out.open( file_name );
    if ( out.is_open() )
    {
        for ( const Block &block : chain )
        {
            out << block.nounce << std::endl;
            out << boost::posix_time::to_iso_string( block.timestamp ) << std::endl;
            out << block.hash << std::endl;
            out << block.message << std::endl;
        }
    }
    else
    {
        return 1;
    }

    out.close();
    return 0;
}

int Blockchain::loadFromFile( std::string file_name )
{
    chain.clear();
    std::ifstream in( file_name );

    std::string nounce_string;
    uint64_t nounce;
    std::string timestamp_string;
    boost::posix_time::ptime timestamp;
    std::string hash;
    std::string message;

    if ( in.is_open() )
    {
        while ( !in.eof() )
        {
            try
            {
                getline( in, nounce_string );
                nounce = std::stoi ( nounce_string );

                getline( in, timestamp_string );
                timestamp = boost::posix_time::from_iso_string( timestamp_string );

                getline( in, hash );
                getline( in, message );

                auto *block = new Block( nounce, timestamp, hash, message );
                push( *block );
            }
            catch ( std::exception &exception )
            {
                return 1;
            }
        }
    }
    else
    {
        return 1;
    }
    in.close();
    return 0;
}

int Blockchain::printLastMessages( int n )
{
    // если запрашиваемое число блоков больше чем есть в цепи, то выводим все
    if( n >= chain.size() )
    {
        std::for_each(chain.rbegin(), chain.rend(), []( const Block &block )
        {
            std::cout << block.message << std::endl;
        });
        return chain.size();
    }
    else
    {
        auto end = chain.rend();
        std::advance( end, n + 1 );

        std::for_each( chain.rbegin(), end, []( const Block &block )
        {
            std::cout << block.message << std::endl;
        });
        return n;
    }
}




