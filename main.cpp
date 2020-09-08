#include <iostream>
#include <ctime>

using namespace std;

class Tranche
{
public:
    time_t timestamp;
    string transactions;
    int nounce;
    string hash(){
        string str;
        //time(&timestamp);
        str = ctime(&timestamp)+transactions + to_string(nounce);
        return str;
    }
};

int main() {
    time_t current1;
    //cout<<hash1(current1, "X gave Y", nounce1)<<endl;
    Tranche one {time(&current1),"X gave $100 to Y", 6};
    cout<< one.hash()<<endl;
    return 0;
}