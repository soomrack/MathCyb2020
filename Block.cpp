
#include <time.h>
#include "Block.h"

using namespace std;

Block::Block(){Name = "UNKNOWN"; Data = "NAN"; Nounce = 0; PrevHash = 0;};

Block::Block(string Nm, string Dt, uint64_t Nnc, uint64_t PrHsh): Name(Nm),Data(Dt), Nounce(Nnc), PrevHash(PrHsh){
    TimeStamp = time(nullptr);
}
ostream& operator<<(ostream &out, const Block &block) {

    out << block.Name << " " << block.TimeStamp
         << " " << block.Data << " "
         << block.Nounce << " " << block.PrevHash;

    return out;
}
Block::~Block()=default;

istream& operator>>(istream &in, Block &block){
    in >> block.Name >>block.TimeStamp >> block.Data >> block.Nounce >> block.PrevHash;
    return in;
};