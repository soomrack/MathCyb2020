#ifndef MATHCYB2020_BLOCK_H
#define MATHCYB2020_BLOCK_H

#include <iostream>
#include <string>
#include <tuple>
#include <ctime>
#include <cstdint>

using namespace std;

struct Block {
private:
    string name;
    string message;
    uint64_t nonce{};
    uint64_t hash{};
    time_t time_stamp{};
public:
    /*
     * Конструкторы и Деструкторы
     */
    Block();
    ~Block() = default;
    explicit Block(const string& name, const string& message, uint64_t hash, uint64_t nounce, time_t time_stamp);
    /*
     * Интерфейс блока
     */
    string get_message();
    string get_name();
    uint64_t get_nonce();
    uint64_t get_hash();
    time_t get_time_stamp();
    //Вернуть всю информацию этого блока
    tuple<string,string,uint64_t,uint64_t,time_t> get_all(){return make_tuple(message,name,nonce,hash,time_stamp);}
    //Block(Block& block);
    /*
     * Оператор вывода всей информации блока
     */
    friend ostream& operator<<(ostream &out,const Block &block);
};
#endif //MATHCYB2020_BLOCK_H
