#ifndef MATHCYB2020_BLOCK_H
#define MATHCYB2020_BLOCK_H

#include <iostream>
#include <ctime>
#include <string>
#include <memory>
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
    Block(const string &data, const uint64_t nounce, const uint64_t prev_hash);

    /* Конструктор,использующийся при выгрузке блока из файла. В этом
     * случае timestamp не должен обновляться*/
    Block(const string &data, const uint64_t nounce, const uint64_t prev_hash,
          const uint64_t timestamp);

    uint64_t computeHash() const;

    uint64_t getPrevHash() const {return prev_hash;}

    string getData() const {return data;}

    uint64_t getIndex() const {return index;}

    uint64_t getNounce() const {return nounce;}

    time_t getTimeStamp() const {return timestamp;}

    void setIndex(uint64_t new_index) {index = new_index;}

    // static bool compareBlocks(const Block &block1, const Block &block2);

public:
    ~Block() = default;
};

bool compareBlocks(const Block &block1, const Block &block2);

#endif //MATHCYB2020_BLOCK_H
