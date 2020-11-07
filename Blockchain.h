#ifndef MATHCYB2020_BLOCKCHAIN_H
#define MATHCYB2020_BLOCKCHAIN_H

#include <iostream>
#include <ctime>
#include <string>
#include <list>
#include <memory>
#include <fstream>
#include <optional>
#include "Block.h"

using namespace std;

class BlockChain {
private:
    list<Block> blockchain;

private:
    /* tmp_blockchain используется для хранения второй цепи при синхронизации.
     * Вынесено в отдельное поле, так как нет функции синхронизации, есть только функции
     * отправления и получения информации, и нужно хранить состояние */
    list<Block> tmp_blockchain;
    /* Так же нужно хранить итератор, чтобы двигаться по обоим блокчейнам */
    optional<list<Block>::reverse_iterator> primary_block_iter;
    list<Block>::reverse_iterator secondary_block_iter;

public:
    BlockChain() : blockchain(), primary_block_iter(nullopt) {}

    bool push(const Block &block);
    bool pop();

    bool printLastData(int n);

    bool saveToFile(const string &filename);
    bool loadFromFile(const string &filename);

    void sendLength(BlockChain &receiver){
        receiver.onLengthReceived(*this, blockchain.size());
    }

    void sendBlock(BlockChain &receiver, const Block &block){
        receiver.onBlockReceived(*this, block);
    }

    void sendMessage(BlockChain &receiver, const int message){
        receiver.onMessageReceived(*this, message);
    }

    void onLengthReceived(BlockChain &sender, uint64_t length);
    void onBlockReceived(BlockChain &sender, const Block &block);
    void onMessageReceived(BlockChain &sender, int message);

    static void merge(BlockChain &main, list<Block> &new_part, int index);

public:
    ~BlockChain() = default;
};

#endif //MATHCYB2020_BLOCKCHAIN_H
