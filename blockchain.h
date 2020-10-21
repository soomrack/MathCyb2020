#ifndef MATHCYB2020_BLOCKCHAIN_H
#define MATHCYB2020_BLOCKCHAIN_H

#include "block.h"
#include <list>
#include <fstream>
#include <iostream>

using namespace std;

class BlockChain {
private:
    list<Block> block_chain;
public:
    /*
     *Конструкторы и Деструкторы
    */
    BlockChain() = default;
    ~BlockChain() = default;
    explicit BlockChain(const Block& block);
    /*
     * Интерфейс
    */
    list<Block> push(const Block& newTail); //Добавление блока в конец "этой" цепи
    list<Block> push_list_of_blocks(const list<Block>& new_chain);
    Block pop(); //Удаление последнего блока из "этой" цепи, возвращает остаток цепочки
    unsigned int print_last_messages(int n); //Печать последних n сообщений "этой" цепи
    int get_chain_length(); // Длина "этой" цепи
    /*
     * Работа с файлами
     */
    unsigned int save_to_file(const string &file_name); // Сохранение в файл цепи(цепей)
    unsigned int load_from_file(const string &file_name); // Загрузка цепи(цепей) из файла
    /*
     * Операторы
     */
    Block& operator[](int index);  //Доступ по индексу в цепи
    friend ostream& operator<<(ostream &out, const BlockChain &chain);  // Вывод всей цепи

    /*
     * Синхронизация блоков
     */
    BlockChain &sendData(int index);

    void loadData(BlockChain &block, int index);

    bool is_block_in_chain(Block &block);

};
Block *get_block_by_id(BlockChain &chain, int index);
BlockChain &sync(BlockChain &chain1, BlockChain &chain2); // Синхронизация двух цепей с учетом правильности
#endif //MATHCYB2020_BLOCKCHAIN_H
