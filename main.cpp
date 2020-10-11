#include <iostream>
#include <ctime>
#include <list>
#include <string.h>

using namespace std;

//cтруктура блока в блокчейне, элементы которого:
//timestamp -- время создания блока
//transactions -- список транзакций
//nounce -- некоторе целое число
//hashValue -- значение хэш-функии от предыдущего блока
struct Tranche{
    time_t timestamp;
    string transactions;
    uint64_t nounce;
    uint64_t hashValue;

public:
    Tranche();
    Tranche(const string transactions, const uint64_t nounce, const uint64_t hashValue);
    Tranche(const Tranche &tranche);

public:
    ~Tranche();// деструктор
};

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
}

int Blockchain::save_to_file(const string filename) {

}

int Blockchain::load_from_file(const string filename) {

}

int Blockchain::print_last_message(const int n) {

}

//хэш-функция(не дописанная): записывает в строку данные блока.
string myhash(Tranche &block){
    string str;
    //time(&timestamp);
    str = ctime(&block.timestamp)+block.transactions + to_string(block.nounce);
    return str;
}

int main() {
//    time_t current1;
//    //cout<<hash1(current1, "X gave Y", nounce1)<<endl;
//    Tranche zero {time(&current1),"X gave $100 to Y", 6, 0};
//    cout<< myhash(zero)<<endl;
    return 0;
}