#include <iostream>
#include <ctime>
#include <list>
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

private:
    ~Tranche(); // деструктор
};

class Blockchain {
private:
    std::list<Tranche> chain;

public:
    Blockchain();

private:
    ~Blockchain();// деструктор

public:
    int push(const Tranche new_tail){ //добавляет новый блок к концу сhain
        chain.push_back(new_tail);
    };

    Tranche pop(); // Удаляет хвостовой блок из цепочки и возвращает его

public:
    int save_to_file(const string filename);

    int load_from_file(const string filename);

public:
    int print_last_message(const int n); // Выводит на консоль сообщения из крайних n блоков
    // и количество выведенных сообщений
};


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