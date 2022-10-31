#include <iostream>
#include <fstream>
#include <string>

using namespace std;
int main() {
    ifstream mf ("peepee.txt");
    string ms;

    if (mf.is_open()){
        mf >> ms;
        cout << ms << "\n";
    }


    return 0;
}