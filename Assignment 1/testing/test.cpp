#include "test.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <time.h>

using namespace std;

void InsultGenerator::initialize(){
    ifstream sourceFile ("pp.txt");     // creating instream object with the arguement

    if (!(sourceFile.is_open())){
        throw FileException();
    }
    else{                
        string line;
        this->col1.reserve(50);
        this->col2.reserve(50);
        this->col3.reserve(50);

        while(getline(sourceFile, line)){
            InsultGenerator::splitString(line);
        }
        sourceFile.close();
    }
    srand(time(NULL));
}// initialize()

// need to pass the vectors in by reference so we can modify them for the program to use
void InsultGenerator::splitString(string input){
    // private helper function to split the string
    int first = input.find('\t');
    int second = input.find('\t', first+1);               // find the second occurrence of (tab)

    this->col1.push_back(input.substr(0, first));                 // substr(pos, len)
    this->col2.push_back(input.substr(first+1, second-first-1));    
    this->col3.push_back(input.substr(second+1, input.length()-second+1));  
}// splitString()

string InsultGenerator::talkToMe(){
    // need to pick a random str from each vect(col1, col2, col3) and then append it, return it
    string insult = "Thou " + this->col1[rand()%50] + " " + this->col2[rand()%50] + " " + this->col3[rand()%50];     // need to fill the indices with random ones everytime
    return insult;
}// talkToMe()

vector<string> InsultGenerator::generate(int num){
    if (num <= 0 || num > 10000){
        throw NumInsultsOutOfBounds();      // if the number is invalid, throw exception
    }
    else{
        set<string> resultSet;
        for (int i=0; i < num; i++){
            while(1){
                // generate the insult
                if(resultSet.insert(InsultGenerator::talkToMe()).second){   // want the version of insert that returns a bool + iterator
                    break;      // break out of the while loop
                }
                else{}  // there is a duplicate, stay within the while until not a duplicate
            }
        }
        vector<string> resultVector(resultSet.begin(), resultSet.end());    // convert resultSet to a vector and return that vector
        return resultVector;
    }   
}

void InsultGenerator::generateAndSave(string filename, int num){
    // check if the filestream can be opened
    ofstream outFile (filename);           // constructor specifies the filename and opening mode, this case output
    if (!(outFile.is_open())){
        throw FileException();
    }
    else{
        // start writing to the text file
        vector<string> results = InsultGenerator::generate(num);
        for (const auto &it : results){
            // write to the text file, print
            outFile << it << "\n";
        }
        outFile.close();                            // close the output file
    }
}

char * FileException::what(){
    return "file exception";
}// what()

char * NumInsultsOutOfBounds::what(){
    return "the number of insults is out of bound";
}// what()
