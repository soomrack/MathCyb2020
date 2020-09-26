#include "blockchain.h"

BlockChain::BlockChain(const Block & block) { this->block_chain.push_back(block); }


int BlockChain::get_chain_length() {  //Длина цепи
    return this->block_chain.size();
}

list<Block> BlockChain::push(const Block & newTail) {  //Добавить блок в конец цепи
    this->block_chain.push_back(newTail);
    return this->block_chain;
}

Block BlockChain::pop() {  //Удалить блок из конца цепи и вернуть этот же блок
    Block lastBlock = this->block_chain.back();
    this->block_chain.pop_back();
    return lastBlock;
}

list<Block> BlockChain::push_list_of_blocks(const list<Block> & new_chain) {  //Добавить list<Block> блоков в конец цепи
    auto index = new_chain.begin();
    while(index != new_chain.end()){
        this->block_chain.push_back(*index);
        index++;
    }
    return this->block_chain;
}
unsigned int BlockChain::print_last_messages(int n) {  //Печать последних n сообщений
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
unsigned int BlockChain::save_to_file(const string &file_name) { //Сохранить в файл
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

unsigned int BlockChain::load_from_file(const string &file_name) {  //Загрузить из файла
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
ostream& operator<<(ostream &out, const BlockChain& chain){ // Вывод всей цепи
    out << "chain length ->" << chain.block_chain.size() << endl;
    out << "blocks: " << endl;

    int j = 0;
    for (const auto & index : chain.block_chain) {
        out << j <<"->\n"<< index << endl;
        j++;
    }
    return out;
}
Block BlockChain::operator[](int index){  //Доступ по индексу в цепи
    auto iterator = this->block_chain.begin();
    if(index <= this->block_chain.size()) {
        cout <<"\n"<< index << "->\n";
        advance(iterator, index);
        return *iterator;
    }
    else {
        cout << "\n" << "index > block.chain.size(), index = block_chain.end() " << "->\n";
        advance(iterator, this->block_chain.size() - 1);
    }
    return *iterator;
}