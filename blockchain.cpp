#include "blockchain.h"

BlockChain::BlockChain(Block & block) {
    this->block_chain.push_back(block);
}


int BlockChain::get_chain_length() {  //Длина цепи
    return this->block_chain.size();
}

list<Block> BlockChain::push(Block & newTail) {  //Добавить блок в конец цепи
    this->block_chain.push_back(newTail);
    return this->block_chain;
}

Block& BlockChain::pop() {  //Удалить блок из конца цепи и вернуть этот же блок
    Block& lastBlock = this->block_chain.back();
    this->block_chain.pop_back();
    return lastBlock;
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
Block& BlockChain::operator[](int index){  //Доступ по индексу в цепи
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

int BlockChain::is_block_in_chain(Block &block) {
    int counter = 0;
    for(auto &i : BlockChain::block_chain){

        if(i.get_hash() == block.get_hash())
            return counter;
        counter++;
    }
    return -1;
}

BlockChain BlockChain::sendData(int index) {
    auto *newBlockChain = new BlockChain;
    index++;
    for (size_t step = index; step < block_chain.size(); step++)
        newBlockChain->push(get_block(step));
    return *newBlockChain;
}

void BlockChain::loadData(BlockChain chain, int index){
    index++;
    for(unsigned int step = index; step < block_chain.size(); step++)
        block_chain.pop_back();
    for (int step = 0; step < chain.get_chain_length() ; step++)
        block_chain.push_back(chain.get_block(step));
}


Block &BlockChain::get_block(int index) {
    auto iterator = block_chain.begin();
    if(index < block_chain.size())
    advance(iterator, index);
    else iterator = block_chain.end();
    return  *iterator;
}


bool sync(BlockChain &chain1, BlockChain &chain2) {


    int step = chain1.get_chain_length();
if(chain1.get_chain_length() < chain2.get_chain_length()) {
    step = chain2.get_chain_length();
    swap(chain1, chain2);
}

  step--;
  for (; step != -1; step--) {
       Block & cur = chain1.get_block(step);
       int pos = chain2.is_block_in_chain(cur);
           if (pos != -1){
                   chain2.loadData(chain1.sendData(step), pos);
                   return true;
           }
    }

    return false;
}


