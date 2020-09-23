#include <iostream>
#include <fstream>

#include <ctime>

#include <cstdint>
#include <string>
#include <list>
#include <tuple>

using namespace std;


struct Block {
private:
    string message;
    string name;
    uint64_t nonce{};
    uint64_t hash{};
    time_t time_stamp{};
public:
    /*
     * Конструкторы и Деструкторы
     */
    Block() = default;
    ~Block() = default;
    explicit Block(const string& name, const string& message, uint64_t hash, uint64_t nounce, time_t time_stamp);
    /*
     * Интерфейс блока
     */
    string get_message(){return message;}
    string get_name(){ return name;}
    uint64_t get_nonce(){ return nonce;}
    uint64_t get_hash(){return hash;}
    time_t get_time_stamp(){ return time_stamp;}
    //Вернуть всю информацию этого блока
    tuple<string,string,uint64_t,uint64_t,time_t> get_all(){return make_tuple(message,name,nonce,hash,time_stamp);}
    //Block(Block& block);
};

Block::Block(const string & name, const string & message, uint64_t hash, uint64_t nounce, time_t time_stamp) {
    this->name = name;
    this->message = message;
    this->hash = hash;
    this->nonce = nounce;
    this->time_stamp = time(nullptr);
}


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
};
BlockChain::BlockChain(const Block & block) { this->block_chain.push_back(block); }


int BlockChain::get_chain_length() {
    return this->block_chain.size();
}

list<Block> BlockChain::push(const Block & newTail) {
    this->block_chain.push_back(newTail);
    return this->block_chain;
}
list<Block> BlockChain::push_list_of_blocks(const list<Block> & new_chain) {
    auto index = new_chain.begin();
    while(index != new_chain.end()){
        this->block_chain.push_back(*index);
        index++;
    }
    return this->block_chain;
}
Block BlockChain::pop() {
    Block lastBlock = this->block_chain.back();
    this->block_chain.pop_back();
    return lastBlock;
}

unsigned int BlockChain::print_last_messages(int n) {
    auto index = this->block_chain.begin();
    if(get_chain_length() >= n)
        advance(index, get_chain_length() - n);
    else
        cout << "chain_length() < n, output = all" << endl;

    for (; index != block_chain.end() ; index++) {
        cout << index->get_message() << endl;
    }
    return 0;
}

/*
 *    Соглашение хранения данных
 *    <string> name, <string> message, <uint64_t> nounce, <uint64_t> hash ,<time_t> time_stamp
 *    Данная строка есть 1 блок.
 */
unsigned int BlockChain::save_to_file(const string &file_name) {
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
        output << i.get_name()<< " " << i.get_message()<< " " << i.get_nonce() << " "<< i.get_hash()<< " " << i.get_time_stamp() << endl;
    }
    output.close();
    return 0;
}

unsigned int BlockChain::load_from_file(const string &file_name) {
    if (file_name.empty()) {
        cerr << "There is no file!";
        return 1;
    }
    else
    {
        ifstream file(file_name);
        while(!file.eof()){

            string message;
            string name;
            uint64_t nonce{};
            uint64_t hash{};
            time_t time_stamp{};

            file >> name >> message >> nonce >> hash >> time_stamp;
            Block newB(name, message, hash, nonce, time_stamp);
                this->block_chain.push_back(newB);
        }
    }
    return 0;
}


/*
 * Hash function TODO
 */
string make_hash(){
    return "none\n";
}

int main() {

    Block block1("Paul2","Message",123,234,0);
    BlockChain chain1(block1);
    cout << chain1.get_chain_length() << endl;

    Block block2("Aaron","Message2",9999,1111,0);
    BlockChain chain2;
    chain2.push(block1);
    chain2.push(block2);
    cout << chain2.get_chain_length() << endl;

    chain2.pop();
    cout << chain2.get_chain_length() << endl;


    string file_name_save = "BlockChain_saver.txt";
    string file_name_load = "BlockChain_loader.txt";


    chain2.load_from_file(file_name_load);
    chain2.save_to_file(file_name_save);
    cout << chain2.get_chain_length() << endl;
    chain2.print_last_messages(3);

    Block b1,b2,b3;
    list<Block> newlist;
    newlist.push_back(b1);
    newlist.push_back(b2);
    newlist.push_back(b3);
    chain2.push_list_of_blocks(newlist);
    cout << chain2.get_chain_length() << endl;



    return 0;
}