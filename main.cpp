#include <iostream>
#include "Block.h"
#include "Block.cpp"
#include<string>
using namespace std;

int main() {
    int nounce = 0;
    string phash = "some hash", data = "some data", name = "Alice";
    Block block(name, data, nounce, phash);
    cout<<block<<endl;

    return 0;
}