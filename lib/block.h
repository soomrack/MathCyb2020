/// @file block.h
/// @brief описание блока

#ifndef MATHCYB2020_BLOCK_H
#define MATHCYB2020_BLOCK_H

#include <string>
#include <ctime>

#include <boost/date_time/posix_time/posix_time.hpp>

class Block
{
public:
    std::size_t index; // индекс блока в цепи
    uint64_t nounce; // параметр proof-of-work
    boost::posix_time::ptime timestamp; // время создания блока
    std::size_t hash; // хэш предыдущего блока, либо 0 для первого блока
    std::string message; // данные, хранящиеся в блоке

    /// @brief конструктор по умолчанию
    Block();

    /// @brief конструктор с параметром message
    /// @param message данные, хранящиеся в блоке
    Block( const std::string message );

    /// @brief констурктор с параметрами, устанавливающий параметр времени создания timestamp
    /// @param nounce параметр proof-of-work
    /// @param hash хэш предыдущего блока, либо 0 для первого блока
    /// @param message данные, хранящиеся в блоке
    Block( const uint64_t nounce, const std::size_t hash, const std::string message );

    /// @brief констурктор с параметрами, устанавливающий параметр времени создания timestamp
    /// @param nounce параметр proof-of-work
    /// @param timestamp время создания блока
    /// @param hash хэш предыдущего блока, либо 0 для первого блока
    /// @param message данные, хранящиеся в блоке
    Block( const uint64_t nounce, const boost::posix_time::ptime timestamp,
           const std::size_t hash, const std::string message );

    /// @brief конструктор копирования
    /// @param ссылка на копируемый блок
    Block( const Block &block );

    /// @brief деструктор
    ~Block();
};

/// @brief функция вычисления хэша от блока
/// @param block блок, от которого нужно вычислить хэш
/// @return хэш
std::size_t getHash( Block &block );

/// @brief функция получения индекса блока
/// @param block блок, индекс которого нужно получить
/// @return индекс
std::size_t getIndex( Block &block );

#endif //MATHCYB2020_BLOCK_H
