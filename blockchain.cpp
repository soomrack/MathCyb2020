#include "blockchain.h"

Blockchain::Blockchain(Block &block) {
  this->blockchain.push_back(block);
}

size_t Blockchain::size() {
  return this->blockchain.size();
}

void Blockchain::push(const Block &block) {
  this->blockchain.push_back(block);
}

void Blockchain::pop() {
  this->blockchain.pop_back();
}

Block& Blockchain::back() {
  return this->blockchain.back();
}

unsigned int Blockchain::print_last_messages(int n) {
  auto index = this->blockchain.begin();
  if(size() >= n)
    advance(index, size() - n);
  else
    cout << "chain_length() < n, output = all" << endl;

  for (; index != blockchain.end() ; index++) {
    cout << index->get_message() << endl;
  }
  return 0;
}

unsigned int Blockchain::save_to_file(const string &file_name) {
  string new_file_name;
  if (file_name.empty()) {
    cout << "Invalid name, saving -> Blockchain_saver.txt" << endl;
    new_file_name = "Blockchain_saver.txt";
  }
  else {
    new_file_name = file_name;
  }
  ofstream output(new_file_name);
  for (auto & i : this->blockchain) {
    output << i.get_name()<< " " << i.get_message()<< " " << i.get_nonce() << " "<< i.get_hash()<< " " << chrono::system_clock::to_time_t(i.get_time_stamp()) << endl;
  }
  output.close();
  return 0;
}

unsigned int Blockchain::load_from_file(const string &file_name) {
  if (file_name.empty()) {
    cerr << "There is no file!";
    return 1;
  }
  else
    {
      ifstream file(file_name);
      while(!file.eof()){

	string message;
	string name;
	string nonce;
	string hash;
	time_t time_stamp;

	file >> name >> message >> nonce >> hash >> time_stamp;
	Block newB(name, message, hash, nonce, chrono::system_clock::from_time_t(time_stamp));
	this->blockchain.push_back(newB);
      }
    }
  return 0;
}
ostream& operator<<(ostream &out, const Blockchain& chain){
  out << "chain length ->" << chain.blockchain.size() << endl;
  out << "blocks: " << endl;

  int j = 0;
  for (const auto & index : chain.blockchain) {
    out << j <<"->\n"<< index << endl;
    j++;
  }
  return out;
}
Block& Blockchain::operator[](int index){
  auto iterator = this->blockchain.begin();
  if(index <= this->blockchain.size()) {
    cout <<"\n"<< index << "->\n";
    advance(iterator, index);
    return *iterator;
  }
  else {
    cout << "\n" << "index > block.chain.size(), index = blockchain.end() " << "->\n";
    advance(iterator, this->blockchain.size() - 1);
  }
  return *iterator;
}

int Blockchain::has_block(Block &block) {
  int counter = 0;
  for(auto &i : Blockchain::blockchain){

    if(i.get_hash() == block.get_hash())
      return counter;
    counter++;
  }
  return -1;
}

Blockchain Blockchain::send_data(int index) {
  auto *newBlockchain = new Blockchain;
  index++;
  for (size_t step = index; step < blockchain.size(); step++)
    newBlockchain->push(get_block(step));
  return *newBlockchain;
}

void Blockchain::load_data(Blockchain chain, int index){
  index++;
  for(unsigned int step = index; step < blockchain.size(); step++)
    blockchain.pop_back();
  for (int step = 0; step < chain.size() ; step++)
    blockchain.push_back(chain.get_block(step));
}


Block &Blockchain::get_block(int index) {
  auto iterator = blockchain.begin();
  if(index < blockchain.size())
    advance(iterator, index);
  else iterator = blockchain.end();
  return  *iterator;
}


bool sync(Blockchain &chain1, Blockchain &chain2) {


  int step = chain1.size();
  if(chain1.size() < chain2.size()) {
    step = chain2.size();
    swap(chain1, chain2);
  }

  step--;
  for (; step != -1; step--) {
    Block & cur = chain1.get_block(step);
    int pos = chain2.has_block(cur);
    if (pos != -1){
      chain2.load_data(chain1.send_data(step), pos);
      return true;
    }
  }

  return false;
}
