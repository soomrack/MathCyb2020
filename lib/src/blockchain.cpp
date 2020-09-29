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
    return ( size_before_push + 1 == chain.size() );
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
        std::for_each( chain.begin(), chain.end(), [] ( const auto &item )
        {
            // TODO Сергей сделать запись в файл
        } );
        out << '\n';
    }
    out.close();
}

int Blockchain::loadFromFile( std::string file_name )
{
    std::string line;

    std::ifstream in( file_name );
    if ( in.is_open() )
    {
        while ( getline( in, line ) )
        {
            //TODO Сергей разбить строку на слова и поместить в новый блок
        }
    }
    in.close();
}

int Blockchain::printLastMessages( int n )
{

    if(n >= chain.size())
    {
        std::for_each(chain.rend(), chain.rbegin(), [](const Block &item)
        {
            std::cout << item.message << ' ';
        });
        std::cout << std::endl;
    }
    else
    {
        auto it = chain.rbegin();
        std::advance(it, chain.size() - n);

        std::for_each(chain.rend(), it, [](const Block &item)
        {
            std::cout << item.message << ' ';
        });
        std::cout << std::endl;

    }
}




