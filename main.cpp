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

public:
    Block(const string &data, const uint64_t nounce, const uint64_t prev_hash)
            : timestamp(), data(data), nounce(nounce), prev_hash(prev_hash) {
        time(&this->timestamp);
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

public:
    ~Block() = default;
};

class BlockChain {
private:
    list<Block> blockchain;

public:
    BlockChain() : blockchain() {}

    bool push(const Block &block) {
        if (!blockchain.empty() && (blockchain.back().computeHash() != block.getPrevHash()))
            return false;

        this->blockchain.push_back(block);
        return true;
    }

    bool pop() {
        if (blockchain.empty())
            return false;
        this->blockchain.pop_back();
        return true;
    }

    bool printLastData(int n){
        if (n > blockchain.size())
            return false;
        auto iter = blockchain.rbegin();
        for (int i = 0; i < n; ++i) {
            cout << iter->getData();
            iter++;
        }
        return true;
    }

    bool saveToFile(const string &filename);

    bool loadFromFile(const string &filename);

public:
    ~BlockChain() = default;
};

int main() {
    return 0;
}