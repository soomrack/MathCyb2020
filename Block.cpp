
#include <time.h>
#include "Block.h"

using namespace std;

Block::Block(){Name = "UNKNOWN"; Data = "NAN"; Nounce = 0; PrevHash = 0;};

Block::Block(string Nm, string Dt, uint64_t Nnc, uint64_t PrHsh): Name(Nm),Data(Dt), Nounce(Nnc), PrevHash(PrHsh){
    TimeStamp = time(nullptr);
}
ostream& operator<<(ostream &out, const Block &block) {

    out <<"Block name: " << block.Name << "; time: " << block.TimeStamp
         << "; Data: " << block.Data << "; Nounce: "
         << block.Nounce << "; Previous Hash: " << block.PrevHash;

    return out;
}
Block::~Block()=default;