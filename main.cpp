#include <iostream>
#include <string>
#include <cstdint>
#include <ctime>
#include <list>
#include <fstream>

using namespace std;

struct Block {
private:
    string message, name;
    uint64_t nounce{}, hash{};
    time_t time_stamp{};
public:
    Block();
    ~Block();
    explicit Block(const string& name, const string& message, uint64_t hash, uint64_t nounce);
    string return_message();

    //Block(Block& block);
};

Block::Block() = default;
Block::~Block() = default;

Block::Block(const string & name, const string & message, uint64_t hash, uint64_t nounce) {
    this->name = name;
    this->message = message;
    this->hash = hash;
    this->nounce = nounce;
    time_stamp = time(nullptr);
}

string Block::return_message() {
    return message;
}


class BlockChain {
private:
    list<Block> block_chain;
public:
    /*
     *Конструкторы и Деструкторы
    */
    BlockChain();
    ~BlockChain();
    explicit BlockChain(const Block& block);
    explicit BlockChain(const list<Block>& new_chain);
    /*
     * Интерфейс
    */
    list<Block> push(const Block& newTail); //Добавление блока в конец "этой" цепи
    list<Block> pop(); //Удаление последнего блока из "этой" цепи, возвращает остаток цепочки
    void print_last_messages(int n); //Печать последних n сообщений "этой" цепи
    int chain_length(); // Длина "этой" цепи
    /*
     * Работа с файлами
     */
    void Save_to_file(ofstream file); // Сохранение в файл цепи(цепей)
    static void Load_from_file(ifstream file); // Загрузка цепи(цепей) из файла
};

BlockChain::BlockChain() = default;
BlockChain::~BlockChain() = default;
BlockChain::BlockChain(const Block & block) { this->block_chain.push_back(block); }
BlockChain::BlockChain(const list<Block> & new_chain) {
    auto i = new_chain.begin();
    while(i != new_chain.end()){
        this->block_chain.push_back(*i);
        i++;
    }
}

int BlockChain::chain_length() {
    return this->block_chain.size();
}

list<Block> BlockChain::push(const Block & newTail) {
    this->block_chain.push_back(newTail);
    return this->block_chain;
}

list<Block> BlockChain::pop() {
    this->block_chain.pop_back();
    return this->block_chain;
}

void BlockChain::print_last_messages(int n) {
    auto i = this->block_chain.begin();
    if(chain_length() >= n)
        advance(i, n);
    else
        cout << "chain_length() < n" << endl;

    for (; i != block_chain.end() ; i++) {
        cout << i->return_message();
    }
}


void BlockChain::Save_to_file(ofstream file) {
    if (!file) {
        cout << "Invalid name, saving -> BlockChain_saver.txt" << endl;
        file.open("BlockChain_saver.txt");
    }
    for (auto i = this->block_chain.begin(); i != this->block_chain.end() ; ++i) {
        //Вывод информации
    }
    file.close();
}

void BlockChain::Load_from_file(ifstream file) {
    if (!file) {
        cerr << "There is no file!";
    }
        //DOTHMS
}

/*
 * Hash function
 */
string make_hash(){
    return "none\n";
}

int main() {

    Block block1("Paul","Message",123,234);
    BlockChain chain1(block1);
    cout << chain1.chain_length() << endl;
    Block block2("Aaron","Message2",9999,1111);
    BlockChain chain2;
    chain2.push(block1);
    chain2.push(block2);
    cout << chain2.chain_length() << endl;
    return 0;
}