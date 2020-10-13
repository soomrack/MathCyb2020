#include <iostream>
#include <ctime>
#include <list>
#include <string.h>
#include <fstream>

using namespace std;

//cтруктура блока в блокчейне, элементы которого:
//timestamp -- время создания блока
//transactions -- список транзакций
//nounce -- некоторе целое число
//hashValue -- значение хэш-функии от предыдущего блока
class Tranche{
    time_t timestamp;
    string transactions;
    uint64_t nounce;
    uint64_t hashValue;

public:
    Tranche();
    Tranche(const time_t timestamp, const string transactions, const uint64_t nounce, const uint64_t hashValue);
    Tranche(const Tranche &tranche);

public:
    ~Tranche();// деструктор

public:
    time_t get_timestamp();
    string get_transactions();
    uint64_t get_nounce();
    uint64_t get_hashValue();
};


Tranche::Tranche() {
    time_t now;
    timestamp = time(&now);
    transactions = "default transactions";
    nounce = 0;
    hashValue = 8;
}

Tranche::Tranche(const time_t new_timestamp, const string new_transactions, const uint64_t new_nounce, const uint64_t new_hashValue) {
    timestamp = new_timestamp;
    transactions = new_transactions;
    nounce = new_nounce;
    hashValue = new_hashValue;
}

Tranche::Tranche(const Tranche &tranche) {
    timestamp = tranche.timestamp;
    transactions = tranche.transactions;
    nounce = tranche.nounce;
    hashValue = tranche.hashValue;
}

time_t Tranche::get_timestamp() {
    return timestamp;
}

string Tranche::get_transactions() {
    return transactions;
}

uint64_t Tranche::get_nounce() {
    return nounce;
}

uint64_t Tranche::get_hashValue() {
    return hashValue;
}

Tranche::~Tranche() {

}

class Blockchain {
private:
    std::list<Tranche> chain;

public:
    Blockchain();

private:
    ~Blockchain();// деструктор

public:
    int push(const Tranche new_tail); //добавляет новый блок к концу сhain
    Tranche pop(); // Удаляет хвостовой блок из цепочки и возвращает его

public:
    int save_to_file(const string filename); //сохраняет блокчейн в файл

    int load_from_file(const string filename); // загружает блокчейн из файла

public:
    int print_last_message(const int n); // Выводит на консоль сообщения из крайних n блоков
                                         // и количество выведенных сообщений
};

int Blockchain::push(const Tranche new_tail) {
    chain.push_back(new_tail);
    return 0;
}

Tranche Blockchain::pop() {
    _List_iterator<Tranche> index = chain.end();
    Tranche tail_block(*index); //здесь CLion попросил сделать деструктор Tranche public вместо private
    chain.pop_back();
    return tail_block;
};

int Blockchain::save_to_file(const string filename) {
    ofstream outFile;
    outFile.open(filename);

    // здесь надо как-то записать блокчейн в файл
    for (auto element : chain) outFile << element << endl; // не работает так! надо разобраться
    outFile.close();
    return 0;
};

int Blockchain::load_from_file(const string filename) {
    ifstream inFile;
    inFile.open(filename);

    // тут надо как-то загрузить блокчейн

    inFile.close();
    return 0;
};

int Blockchain::print_last_message(const int n) {
    return 0;
};

//хэш-функция(не дописанная): записывает в строку данные блока.
string myhash(Tranche &block){
    string str;
    //time(&timestamp);
    str = to_string(block.get_timestamp())+block.get_transactions() + to_string(block.get_nounce());
    return str;
};

int main() {
    time_t current1;
    //cout<<hash1(current1, "X gave Y", nounce1)<<endl;
    Tranche zero(time(&current1),"X gave $100 to Y", 6, 0);
    //cout<< myhash(zero)<<endl;
    return 0;
}