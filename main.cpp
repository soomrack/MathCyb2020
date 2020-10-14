#include <iostream>
#include <cstdio>
#include <ctime>
#include <string>
#include <list>

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

    uint64_t computeHash() const {
        return 0;
    }

    uint64_t getPrevHash() const {
        return this->prev_hash;
    }

    string getData() const {
        return this->data;
    }

    uint64_t getIndex() const {
        return this->index;
    }

    void setIndex(uint64_t newIndex) {
        this->index = newIndex;
    }

public:
    ~Block() = default;
};

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

    bool onLengthReceived(BlockChain &sender, const uint64_t anotherLength);
    bool onBlockReceived(BlockChain &sender, const Block &anotherBlock);
    bool onSuccessMessageReceived(BlockChain &sender, const string &successMessage);

    bool synchronization(BlockChain &anotherBlockChain);

    uint64_t getLength(){
        return blockchain.size();
    }

public:
    ~BlockChain() = default;
};

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
    return 0;
}