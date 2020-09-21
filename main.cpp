#include <iostream>
#include <string>
#include <cstdint>
#include <ctime>
#include <list>
#include <fstream>
#include <tuple>
using namespace std;

struct Block {
private:
    string message, name;
    uint64_t nounce{}, hash{};
    time_t time_stamp{};
public:
    /*
     * Конструкторы и Деструкторы
     */
    Block();
    ~Block();
    explicit Block(const string& name, const string& message, uint64_t hash, uint64_t nounce,time_t time_stamp);
    /*
     * Интерфейс блока
     */
    string return_message(){return message;}
    string return_name(){ return name;}
    uint64_t return_nounce(){ return nounce;}
    uint64_t return_hash(){return hash;}
    time_t return_time_stamp(){ return time_stamp;}
    //Вернуть всю информацию этого блока
    tuple<string,string,uint64_t,uint64_t,time_t> return_all(){return make_tuple(message,name,nounce,hash,time_stamp);}
    //Block(Block& block);
};

Block::Block() = default;
Block::~Block() = default;
Block::Block(const string & name, const string & message, uint64_t hash, uint64_t nounce,time_t time_stamp) {
    this->name = name;
    this->message = message;
    this->hash = hash;
    this->nounce = nounce;
    this->time_stamp = time(nullptr);
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
    void Save_to_file(const string &file_name); // Сохранение в файл цепи(цепей)
    void Load_from_file(const string &file_name); // Загрузка цепи(цепей) из файла
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

/*
 *    Соглашение хранения данных
 *    <string> name, <string> message, <uint64_t> nounce, <uint64_t> hash ,<time_t> time_stamp
 *    Данная строка есть 1 блок.
 */
void BlockChain::Save_to_file(const string &file_name) {
    string new_file_name;
    if (file_name.empty()) {
        cout << "Invalid name, saving -> BlockChain_saver.txt" << endl;
        new_file_name = "BlockChain_saver.txt";
    }
    else {
        new_file_name = file_name;
    }
    ofstream output(new_file_name);
    for (auto & i : this->block_chain) {
        output << i.return_name()<< " " << i.return_message()<< " " << i.return_nounce() << " "<< i.return_hash()<< " " << i.return_time_stamp() << endl;
    }
    output.close();
}

void BlockChain::Load_from_file(const string &file_name) {
    if (file_name.empty()) {
        cerr << "There is no file!";
    }
    else
    {
        ifstream file(file_name);
        while(!file.eof()){

            string message, name;
            uint64_t nounce{}, hash{};
            time_t time_stamp{};

            file >> message >> name >> nounce >> hash >> time_stamp;
            Block newB(name, message, hash, nounce, time_stamp);
                this->block_chain.push_back(newB);
        }
    }
}


/*
 * Hash function
 */
string make_hash(){
    return "none\n";
}

int main() {

    Block block1("Paul2","Message",123,234,0);
    BlockChain chain1(block1);
    cout << chain1.chain_length() << endl;

    Block block2("Aaron","Message2",9999,1111,0);
    BlockChain chain2;
    chain2.push(block1);
    chain2.push(block2);
    cout << chain2.chain_length() << endl;

    chain2.pop();
    cout << chain2.chain_length() << endl;


    string file_name_save = "BlockChain_saver.txt";
    string file_name_load = "BlockChain_loader.txt";

    chain2.Load_from_file(file_name_load);
    chain2.Save_to_file(file_name_save);
    cout << chain2.chain_length() << endl;
    //cout << chain2.

    return 0;
}