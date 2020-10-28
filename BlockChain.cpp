//
// Created by Brave on 28.09.2020.
//

#include "BlockChain.h"

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

// Нужна функция для вывода последнего совпадающего блока в двух блокчейнах. 
// Для этого нужно получить эти два блокчейна. Также нужна проверять хэш или 
