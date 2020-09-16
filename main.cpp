#include <iostream>
#include <string>
#include <cstdint>
#include <ctime>
#include <list>
#include <fstream>
#include<vector>

using namespace std;

struct Block {
private:
    string data, name;
    uint64_t nounce{}, hash{};
    time_t time_stamp{};
public:
    Block();
    Block(const string& name, const string& data, uint64_t hash, uint64_t nounce);
    //Block(Block& block);
    //~Block();
};

Block::Block() = default;
Block::Block(const string & name, const string & data, uint64_t hash, uint64_t nounce) {}

class BlockChain {
private:
    static list<Block> chain;
public:

    /*
     *Конструкторы
    */
    BlockChain();
    explicit BlockChain(const Block& block);
    explicit BlockChain(const list<Block>& block);
    /*
     * Интерфейс
    */
    static list<Block> push(const Block& newTail); //Добавление блока в конец
    static list<Block> pop(); //Удаление последнего блока из цепи, возвращает остаток цепочки
    static void print_last_messages(int n); //Печать последних n сообщений
    static int chain_length(); // Длина цепи
    /*
     * Работа с файлами
     */
    static void Save_to_file(FILE* file); // Сохранение в файл цепи
    static void Load_from_file(FILE* file); // Загрузка цепи из файла
};

BlockChain::BlockChain() = default;
BlockChain::BlockChain(const Block & block) {/*chain.push_back(block)*/}
BlockChain::BlockChain(const list<Block>& block) {}

/*int BlockChain::chain_length() {return chain.size();}*/

/*list<Block> BlockChain::push(const Block& newTail) {
//    chain.push_back(newTail);
//    return chain;
}

list<Block> BlockChain::pop() {
//    chain.pop_back();
//    return chain;
}*/

void BlockChain::print_last_messages(int n) {}

void BlockChain::Save_to_file(FILE *file) {
//    if(!file) {
//       cout << "Invalid name, saving -> BlockChain_saver.txt" << endl;
//       ofstream output("BlockChain_saver.txt");
//    }
//    else
//        ofstream output(file);
//
//    for (auto i = chain.begin(); i != chain.end() ; ++i) {
//
//    }
}

void BlockChain::Load_from_file(FILE *file) {
    if(file){
        //DOSMTH
    }
    else
        cerr << "There is no file!";
}

string make_hash(){ // hash_function
    return "none\n";
}

int main() {

    return 0;
}