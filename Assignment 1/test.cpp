#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include "insultgenerator_19ml105.h"

using namespace std;

int main(){
    InsultGenerator ig;

    try {
		ig.initialize();
	} catch (FileException& e) {
		cerr << e.what() << endl;
		return 1;
	}

    cout << "file loaded" << endl;
    return 0;
}