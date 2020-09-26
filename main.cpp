#include "block.h"
#include "blockchain.h"
#include <hash/sha256.cpp>
#include <ctime>
using namespace std;

void make_hash(Block& block);

int main() {

    Block block1("Paul2","Message",123,234,0);
    BlockChain chain1(block1);
    //cout << chain1.get_chain_length() << endl;

    Block block2("Aaron","Message2",9999,1111,0);
    BlockChain chain2;
    chain2.push(block1);
    chain2.push(block2);
    //cout << chain2.get_chain_length() << endl;

    chain2.pop();
    //cout << chain2.get_chain_length() << endl;


    string file_name_save = "BlockChain_saver.txt";
    string file_name_load = "BlockChain_loader.txt";


    chain2.load_from_file(file_name_load);
    chain2.save_to_file(file_name_save);
    //cout << chain2.get_chain_length() << endl;
    //chain2.print_last_messages(3);


    //cout << chain2.get_chain_length() << endl;
    //cout << chain2[102];
    make_hash(chain2[2]);
    return 0;
}

void make_hash(Block &block) {
    string string_to_hash = to_string(block.get_nonce()) + block.get_message();
    SHA256 sha256;
    cout << string_to_hash  << " "<< sha256("string_to_hash") <<endl;
}