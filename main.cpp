#include <iostream>
#include <ctime>
#include <list>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <iterator>

using namespace std;

//cтруктура блока в блокчейне, элементы которого:
//timestamp -- время создания блока
//transactions -- список транзакций
//nounce -- некоторе целое число
//hashValue -- значение хэш-функии от предыдущего блока
class Tranche{

public:
    Tranche();
    Tranche(const time_t timestamp, const string transactions, const uint64_t nounce, const uint64_t hashValue);
    Tranche(const Tranche &tranche);

    uint64_t hashValue;
    time_t timestamp;
    string transactions;
    uint64_t nounce;
public:
    ~Tranche();// деструктор

public:
    string get_timestamp();
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

ostream& operator<<(ostream &out, const Tranche &block) {
    out << block.timestamp << " " << block.transactions
        << " " << block.nounce << " "
        << block.hashValue;
    return out;
}

istream& operator>>(istream &in, Tranche &block){
    in >> block.transactions >>block.timestamp >> block.nounce >> block.hashValue;
    return in;
};

string Tranche::get_timestamp() {
    return ctime(&timestamp);
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

    ~Blockchain();
    // деструктор

public:
    int push(const Tranche new_tail); //добавляет новый блок к концу сhain
    Tranche pop(); // Удаляет хвостовой блок из цепочки и возвращает его

public:
    int save_to_file(const string filename); //сохраняет блокчейн в файл

    int load_from_file(const string filename); // загружает блокчейн из файла

public:
    int print_last_message(const int n); // Выводит на консоль сообщения из крайних n блоков
                                         // и количество выведенных сообщений
public:
    int get_length(const Tranche chain); // выводит длину цепочки блокчейна chain

public:
    Tranche get_last(); // Возвращает последний блок цепочки блокчейна

    friend ostream& operator<< (ostream &out, const Blockchain &chain); //для перегрузки оператора <<
};

Blockchain::Blockchain(){
    std::list<Tranche> new_chain;
    chain = new_chain;
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

ostream& operator<<(ostream &out, const Blockchain &this_chain){
    out<< "chain length = "<< this_chain.chain.size()<<'\n'<<"blocks: "<<endl;
    for(auto index = this_chain.chain.begin(); index != this_chain.chain.end(); ++index){
        out << *index << endl;
    }
    return out;
}


int Blockchain::save_to_file(const string filename) {
    ofstream outFile;
    outFile.open(filename, ios_base::trunc);
    if(outFile.fail())
        std::cout<<"unable to open the file"<<endl;
    for (const auto &element : chain) outFile << element << endl;
    outFile.close();
    return 0;
};

int Blockchain::load_from_file(string filename) {
    ifstream inFile(filename);
    istream_iterator<Tranche> begin(inFile), end;
    list<Tranche> chain_(begin, end);
    chain = chain_;
    inFile.close();
    return 0;
}

int Blockchain::print_last_message(const int n) {
    return 0;
}

Blockchain::~Blockchain() {

};

//хэш-функция(не дописанная): записывает в строку данные блока.
string myhash(Tranche &block){
    string str;
    //time(&timestamp);
    str = block.get_timestamp()+block.get_transactions() + to_string(block.get_nounce());
    return str;
};

//интерфейс синхронизации (протокола консенсуса)
int send_data(string address, Blockchain my_blockchain); // Отправляет имеющийся блокчейн получателю на address, который состоит из IP и port
int load_data(string address, Blockchain loaded_blockchain); // Загружает блокчейн отправителя (его IP и port в address)
int send_length(string address, int length); // Отправляет длину блокчейна (length) получателю (его IP и port в address)
int send_block(string address, Tranche block, int block_number); // Отправляет block и порядковый номер блока в цепочке
                                                                 // (block_number) на address
int send_success(string address); // Отправляет сообщение о получении блока на address


int main() {
    time_t current1;
    //cout<<hash1(current1, "X gave Y", nounce1)<<endl;
    Tranche zero(time(&current1),"X gave $100 to Y", 6, 0);
    Blockchain test_chain;
    Blockchain loaded_chain;
    test_chain.push(zero);
    test_chain.save_to_file("test_chain.txt");
    loaded_chain.load_from_file("test_chain.txt");
    Tranche one;
    one = loaded_chain.pop();
    cout<< one <<endl;
    return 0;
}