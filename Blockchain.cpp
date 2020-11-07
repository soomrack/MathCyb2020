#include <iostream>
#include <ctime>
#include <string>
#include <list>
#include <memory>
#include <fstream>
#include <optional>
#include "Blockchain.h"

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

/* Messages types:
 * 1 - send block
 * 2 - ready for sending blocks
 * 3 - stop synchronization */
void BlockChain::onBlockReceived(BlockChain &sender, const Block &block){
    if (!tmp_blockchain.empty() && block.computeHash() != tmp_blockchain.front().getPrevHash()){
        sendMessage(sender, 3);
        return;
    }
    if (block.getIndex() == blockchain.back().getIndex())
        secondary_block_iter = blockchain.rbegin();
    if (block.getIndex() > blockchain.back().getIndex()) {
        tmp_blockchain.push_front(block);
        sendMessage(sender, 1);
    }
    else{
        if (compareBlocks(block, *secondary_block_iter) || block.getIndex() == 0){
            merge(*this, tmp_blockchain, block.getIndex());
            sendMessage(sender, 3);
        }
        else{
            tmp_blockchain.push_front(block);
            secondary_block_iter++;
            sendMessage(sender, 1);
        }
    }
}

/* Messages types:
 * 1 - send block
 * 2 - ready for sending blocks
 * 3 - stop synchronization */
void BlockChain::onLengthReceived(BlockChain &sender, const uint64_t length){
    if (blockchain.size() > length) {
        primary_block_iter = blockchain.rbegin();
        sendMessage(sender, 2);
    }
    else if (blockchain.size() < length){
        tmp_blockchain = {};
        sendMessage(sender, 1);
    }
    else
        sendMessage(sender, 3);
}

/* Messages types:
 * 1 - send block
 * 2 - ready for sending blocks
 * 3 - stop synchronization */
void BlockChain::onMessageReceived(BlockChain &sender, const int message){
    switch (message) {
        case 1:
            if (!primary_block_iter.has_value())
                primary_block_iter = blockchain.rbegin();
            sendBlock(sender, *(*primary_block_iter)++);
            break;
        case 2:
            tmp_blockchain = {};
            sendMessage(sender, 1);
            break;
        case 3:
            if (primary_block_iter.has_value())
                primary_block_iter = nullopt;
        default:
            return;
    }
}

void BlockChain::merge(BlockChain &main, list<Block> &new_part, int index){
    while (main.blockchain.back().getIndex() > index)
        main.pop();
    for (Block &block : new_part)
        main.push(block);
}

bool BlockChain::printLastData(int n){
    auto iter = blockchain.rbegin();
    for (int i = 0; i < n && i < blockchain.size(); ++i) {
        cout << iter->getData() << " ";
        iter++;
    }
    cout << endl;
    return true;
}

using namespace std;
