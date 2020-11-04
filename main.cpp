#include <iostream>
// #include <cstdio>
#include <ctime>
#include <string>
#include <list>
#include <memory>
#include <fstream>
#include <optional>
#include <hash_map>

using namespace std;

class Block {
private:
    time_t timestamp;
    string data;
    uint64_t nounce;
    uint64_t prev_hash;
    uint64_t index;

public:
    Block(const string &data, const uint64_t nounce, const uint64_t prev_hash)
            : timestamp(), data(data), nounce(nounce), prev_hash(prev_hash) {
        time(&this->timestamp);
        index = 0;
    }

    /* Конструктор,использующийся при выгрузке блока из файла. В этом
     * случае timestamp не должен обновляться*/
    Block(const string &data, const uint64_t nounce, const uint64_t prev_hash,
          const uint64_t timestamp): timestamp(timestamp), data(data), nounce(nounce),
          prev_hash(prev_hash) {
        index = 0;
    }

    uint64_t computeHash() const;

    uint64_t getPrevHash() const {
        return this->prev_hash;
    }

    string getData() const {
        return this->data;
    }

    uint64_t getIndex() const {
        return this->index;
    }

    uint64_t getNounce() const {
        return this->nounce;
    }

    time_t getTimeStamp() const {
        return this->timestamp;
    }

    void setIndex(uint64_t new_index) {
        this->index = new_index;
    }

public:
    ~Block() = default;
};

uint64_t Block::computeHash() const {
    hash<string> hasher;
    string block_info = to_string(timestamp) + to_string(nounce) +
            to_string(prev_hash) + data;
    return hasher(block_info);
}

bool compareBlocks(const Block &block1, const Block &block2) {
    if (block1.computeHash() == block2.computeHash())
        return true;
    return false;
}

class BlockChain {
private:
    list<Block> blockchain;

public:
    BlockChain() : blockchain() {}

    bool push(const Block &block);
    bool pop();

    bool printLastData(int n);

    bool saveToFile(const string &filename);
    bool loadFromFile(const string &filename);

    /* Так как пока нет взаимодействия по сети, то отправка данных заключается
    * в вызове у другого блокчейна функции, обрабатывающей отправленную информацию*/
    bool sendLength(BlockChain &receiver){
        receiver.onLengthReceived(*this, blockchain.size());
    }

    bool sendBlock(BlockChain &receiver, const Block &block){
        receiver.onBlockReceived(*this, block);
    }

    bool sendSuccessMessage(BlockChain &receiver){
        receiver.onSuccessMessageReceived(*this, "Success");
    }

    bool onLengthReceived(BlockChain &sender, const uint64_t another_length);
    bool onBlockReceived(BlockChain &sender, const Block &another_block);
    bool onSuccessMessageReceived(BlockChain &sender, const string &success_message);

    bool synchronization(BlockChain &another_blockChain);

    uint64_t getLength(){
        return blockchain.size();
    }

public:
    ~BlockChain() = default;
};

/* Функция сохраняет blockchain в файл. Каждый блок с новой строки в формате:
 * timestamp nounce hash data.size data
 * data может содержать пробелы и переносы строк.*/
bool BlockChain::saveToFile(const string &filename) {
    ofstream fout(filename);
    if (!fout)
        return false;

    for (const auto &block : blockchain) {
        fout << to_string(block.getTimeStamp()) << " ";
        fout << to_string(block.getNounce()) << " ";
        fout << to_string(block.getPrevHash()) << " ";
        fout << to_string(block.getData().size()) << " ";
        fout << block.getData() << endl;
    }
    fout.close();
    return true;
}

/* Функция загружает blockchain из файла. Каждый блок должен быть написан
 * с новой строки в формате:
 * timestamp nounce hash data.size data
 * data может содержать пробелы и переносы строк.*/
bool BlockChain::loadFromFile(const string &filename) {
    ifstream fin(filename);
    if (!fin)
        return false;

    blockchain.clear();
    time_t timestamp;
    uint64_t nounce;
    uint64_t hash;
    uint64_t data_size = 0;
    char tmp[2];

    while (fin >> timestamp){
        fin >> nounce >> hash >> data_size;
        unique_ptr<char[]> buffer(new char[data_size]);
        fin.read(tmp, 1);  // Считывается пробел между data_size и data
        fin.read(buffer.get(), data_size);
        string data(buffer.get(), data_size);
        auto block = Block(data, nounce, hash, timestamp);
        push(block);
    }

    fin.close();
    return true;
}

bool BlockChain::push(const Block &block) {
    if (!blockchain.empty() && (blockchain.back().computeHash() != block.getPrevHash()))
        return false;

    this->blockchain.push_back(block);
    blockchain.back().setIndex(blockchain.size() - 1);
    return true;
}

bool BlockChain::pop() {
    if (blockchain.empty())
        return false;
    this->blockchain.pop_back();
    return true;
}

bool synchronization(const BlockChain &anotherBlockChain){

}

bool BlockChain::printLastData(int n){
    auto iter = blockchain.rbegin();
    for (int i = 0; i < n && i < blockchain.size(); ++i) {
        cout << iter->getData();
        iter++;
    }
    return true;
}

int main() {
    Block block1 = Block("Some data", 1, 0);
    uint64_t hash1 = block1.computeHash();
    Block block2 = Block("Some more data", 2, hash1);
    BlockChain chain = BlockChain();
    chain.push(block1);
    chain.push(block2);
    return 0;
}