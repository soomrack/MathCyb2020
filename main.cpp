#include <iostream>
#include <string>
#include <ctime>
#include <utility>

using namespace std;

struct Block{
    string data, name, hash; // data, name, hash
    int nounce; // some nounce
    time_t time_stamp; //time

    Block(string name, string data, string hash, int nounce) : name(std::move(name)),data(std::move(data)),hash(std::move(hash)), nounce(nounce) { // construct block
        time_stamp = time(nullptr);
    }
};

string make_hash(){ // hash_function
    return "hash";
}

class Chain{ // block_chain class

    static Block *block;
    Chain *next;


    static void entering_data(){
        int nounce;
        cin >> nounce;
        string name, data, hash;
        cin >> name >> data;
        hash = make_hash();
        block->data = data;
        block->name = name;
        block->hash = hash;
        block->nounce = nounce;

    }
};

int main() {

    return 0;
}