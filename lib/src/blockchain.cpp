#include <algorithm>
#include <iostream>
#include <fstream>

#include "blockchain.h"

Blockchain::Blockchain() {}

Blockchain::~Blockchain() {}

int Blockchain::push( const Block &new_tail )
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

Block Blockchain::back()
{
    return chain.back();
}

Block Blockchain::getBlockByIndex( std::size_t index )
{
    std::size_t current_index = 0;
    for ( auto block = chain.begin(); block != chain.end(); block++ )
    {
        if ( current_index == index )
            return *block;
        else
            current_index++;
    }
}

int Blockchain::size()
{
    return chain.size();
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
    std::string hash_string;
    std::size_t hash;
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

                getline( in, hash_string );
                hash = boost::lexical_cast<std::size_t>( hash_string );

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

Blockchain Blockchain::sendData( std::size_t from )
{
    Blockchain data = Blockchain();
    for ( int index = from; index != chain.size(); index++ )
    {
        data.push( getBlockByIndex( index ));
    }
    return data;
}

void Blockchain::loadData( Blockchain data, std::size_t from )
{
    // очистим все блоки, которые успели сгенерироваться посде последней синхронизации
    for ( int index = from; index != chain.size(); index++ )
    {
        chain.pop_back();
    }

    // добавим навый остаток цепи
    for ( int index = 0; index != data.size(); index++ )
    {
        chain.push_back( data.getBlockByIndex( index ));
    }
}

std::size_t Blockchain::isBlockInChain( Block &sought )
{
    for ( auto block = chain.end(); block != chain.begin(); block-- )
    {
        if ( getHash(*block ) == getHash(sought ) )
        {
            return block->index;
        }
    }
    return -1;
}

int synchronize( Blockchain &alice, Blockchain &bob )
{
    if ( alice.size() > bob.size() )
    {
        // Alice ничего не делает, bob добавляет блоки alice
        for ( int alice_index = alice.size(); alice_index != 0; alice_index-- )
        {
            Block sought = alice.getBlockByIndex( alice_index );
            std::size_t bob_index = bob.isBlockInChain( sought );
            if ( bob_index != -1 )
            {
                bob.loadData( alice.sendData( alice_index ), bob_index );
                return 0;
            }
        }
        return 1;
    }
    else
    {
        // Bob ничего не делает, Alice добавляет блоки bob
        for ( int bob_index = bob.size(); bob_index != 0; bob_index-- )
        {
            Block sought = bob.getBlockByIndex( bob_index );
            std::size_t alice_index = alice.isBlockInChain( sought );
            if ( alice_index != -1 )
            {
                alice.loadData( bob.sendData( bob_index ), alice_index );
                return 0;
            }
        }
        return 1;
    }
}


