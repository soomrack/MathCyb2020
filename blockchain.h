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
    explicit BlockChain(Block& block);
    /*
     * Интерфейс
    */
    list<Block> push(Block& newTail); //Добавление блока в конец "этой" цепи
    Block& get_block(int index); // Получение блока по индексу
    Block& pop(); //Удаление последнего блока из "этой" цепи, возвращает остаток цепочки
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
    BlockChain sendData(int index);

    void loadData(BlockChain chain, int index);

    int is_block_in_chain(Block &block);

};

bool  sync(BlockChain &chain1, BlockChain &chain2); // Синхронизация двух цепей с учетом правильности
#endif //MATHCYB2020_BLOCKCHAIN_H
