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
    /// @return код ошибки (0 - успех, 1 - ошибка)
    int push( const Block &new_tail );

    /// @brief удаление последнего блока из цепи
    /// @return возвращает удаленный хвост цепи
    Block pop();

    /// @brief получение последнего блока из цепи
    /// @return возвращает хвост цепи
    Block back();

    /// @brief получение блока по индексу
    /// @return возвращает искомый блок
    Block getBlockByIndex( std::size_t index );

    /// @brief получение размера блокчейна
    /// @return длина цепи
    int size();

    /// @brief запись в файл информации о блокчейне
    /// @param file_name путь к файлу для записи
    /// @return код ошибки (0 - успех, 1 - ошибка)
    int saveToFile( std::string file_name );

    /// @brief чтение записи информации о блокчейне
    /// @param file_name путь к файлу для чтения
    /// @return код ошибки (0 - успех, 1 - ошибка)
    int loadFromFile( std::string file_name );

    /// @brief вывод на консоль n последних сообщений в обратном порядке
    /// @param количество сообщений, которое нужно вывести
    /// @return число реально выведенных сообщений (если их было меньше, чем запрашиваемое число)
    int printLastMessages( int n );

    /// @brief функция отправки данных другому блокчейну
    /// @param from индекс, начиная с которого нужно отправить цепь
    /// @return цепь от запришиваемого индекса и до конца
    Blockchain sendData( std::size_t from );

    /// @brief функция получения данных из другого блокчейна
    /// @param data цепь, которую нужно присоединить
    /// @param from с какого индекса нужно прицепить нужную цепь
    void loadData( Blockchain data, std::size_t from );

    /// @brief функция проверки, есть ли блок в текущей цепи
    /// @param block искомый блок
    /// @return индекс вхождения элемента в цепи, если он есть, и -1, если его нет
    std::size_t isBlockInChain( Block &sought );
};

/// @brief функция синхронизации двух блокчейнов
/// @param alice первый блокчейн
/// @param bob второй блокчейн
/// @return код ошибки (0 - успех, 1 - ошибка)
int synchronize( Blockchain &alice, Blockchain &bob );

#endif //MATHCYB2020_BLOCKCHAIN_H
