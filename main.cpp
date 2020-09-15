#include <iostream>
#include <ctime>

using namespace std;

class Blockchain{
public:
    void createTranche(){
    };
};

//cтруктура блока в блокчейне, элементы которого:
//timestamp -- время создания блока
//transactions -- список транзакций
//nounce -- некоторе целое число
//hashValue -- значение хэш-функии от предыдущего блока
struct Tranche{
    time_t timestamp;
    string transactions;
    int nounce;
    double hashValue;
};

//хэш-функция(не дописанная): записывает в строку данные блока.
string myhash(Tranche &block){
    string str;
    //time(&timestamp);
    str = ctime(&block.timestamp)+block.transactions + to_string(block.nounce);
    return str;
}

int main() {
    time_t current1;
    //cout<<hash1(current1, "X gave Y", nounce1)<<endl;
    Tranche zero {time(&current1),"X gave $100 to Y", 6, 0};
    cout<< myhash(zero)<<endl;
    return 0;
}