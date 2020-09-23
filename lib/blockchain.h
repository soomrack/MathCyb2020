/// @file blockchain.h
/// @brief описание блокчейна

#ifndef MATHCYB2020_BLOCKCHAIN_H
#define MATHCYB2020_BLOCKCHAIN_H

#include <list>

#include "block.h"

class Blockchain : public Block
{
private:
    std::list<Block> chain;

public:
    /// @brief конструктор по умолчанию
    Blockchain();

    /// @brief деструктор
    ~Blockchain();

    /// @brief добавление новый блок
    /// @param new_tail добавляемый хвост
    /// @return код ошибки
    int push( const Block new_tail );

    /// @brief удаление последнего блока из цепи
    /// @return возвращает удаленный хвост цепи
    Block pop();

    /// @brief запись в файл информации о блокчейне
    /// @param file_name путь к файлу для записи
    /// @return код ошибки
    int saveToFile( std::string file_name );

    /// @brief чтение записи информации о блокчейне
    /// @param file_name путь к файлу для чтения
    /// @return код ошибки
    int loadFromFile( std::string file_name );

    /// @brief вывод на консоль n последних сообщений
    /// @param количество сообщений, которое нужно вывести
    /// @return число реально выведенных сообщений (если их было меньше, чем запрашиваемое число)
    int printLastMessages( int n );
};

#endif //MATHCYB2020_BLOCKCHAIN_H
