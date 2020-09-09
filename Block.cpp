
#include <time.h>
#include "Block.h"

using namespace std;

Block::Block(string Nm, string Dt, int Nnc, string PrHsh): Name(Nm),Data(Dt), Nounce(Nnc), PrevHash(PrHsh){
    TimeStamp = time(nullptr);
}
ostream& operator<<(ostream &out, const Block &block) {

    out <<"Block name: " << block.Name << "; time: " << block.TimeStamp
         << "; Data: " << block.Data << "; Nounce: "
         << block.Nounce << "; Previous Hash: " << block.PrevHash;

    return out;
}