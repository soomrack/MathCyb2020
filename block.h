#ifndef MATHCYB2020_BLOCK_H
#define MATHCYB2020_BLOCK_H

#include <iostream>
#include <string>
#include <tuple>
#include <cstdint>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;

struct Block {
private:
    string name;
    string message;
    uint64_t nonce{};
    uint64_t hash{};
    typedef boost::posix_time::ptime time;
    time time_stamp{};
public:
    /*
     * Конструкторы и Деструкторы
     */
    Block();
    ~Block() = default;
    explicit Block(const string& name, const string& message, uint64_t hash, uint64_t nonce);
    explicit Block(const string& name, const string& message, uint64_t nonce, time time_stamp);
    /*
     * Интерфейс блока
     */
    string get_message();
    string get_name();
    uint64_t get_nonce();
    uint64_t get_hash();
    time get_time_stamp();

    void insert_hash(int block_hash);
    //Вернуть всю информацию этого блока
    tuple<string,string,uint64_t,uint64_t,time> get_all(){return make_tuple(message,name,nonce,hash,time_stamp);}

    /*
     * Оператор вывода всей информации блока
     */
    friend ostream& operator<<(ostream &out,const Block &block);


};
/*
 * Получение хэша
 */
size_t getHash( Block& block);

#endif //MATHCYB2020_BLOCK_H
