//
// Created by Brave on 28.09.2020.
//

#include "BlockChain.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

BlockChain::BlockChain() {
    Chain.emplace_back(Block(0, "Genesis Block"));
    Difficulty = 6;
}

void BlockChain::AddBlock(Block B_New) {
    B_New.prev_hash = GetLastBlock().GetHash();
    B_New.MiningBlock(Difficulty);
    Chain.push_back(B_New);
}

Block BlockChain::GetLastBlock() const{
    return Chain.push_back();
}

int BlockChain::get_length() {
    return Chain.size();
}

Block BlockChain::GetBlock(int index)
{
	if(index < Chain.get_length())
	{
		return Chain[index];
	}
	else 
	{
		return NULL;
	}
}


int Blockchain::load_data(string File){
    string line;
    ifstream in(File); 
    if (in.is_open())
    {
        while (getline(in, line))
        {
            cout << line << endl;
        }
    }
    in.close();  	

    return 0;
}; 



int Blockchain::save_data(string File, string Text){
    ofstream out("File", ios::app);
    if (out.is_open())
         out << Text << endl;
    out.close(); 
	
    return 0;
};



// Synchronization

void sync(string address_1, string address_2)
{
	BlockChain first = load_data(string address_1);
	BlockChain second = load_data(string address_2);
	if(first.get_length() < second.get_length())
	{
		for(int i = first.get_length(); i < second.get_length(); i++)
		{
			send_block(address_1,second.GetBlock(i),i);
		}
	}
	else if(first.get_length() > second.get_length())
	{
		for(int i = second.get_length(); i < first.get_length(); i++)
		{
			send_block(address_2,first.GetBlock(i),i);
		}
	}
}

int send_length(string address, int length);
 
int send_block(string address, Block block, int block_number);

int send_success(string address);

BlockChain load_data(string address);

