#include "insultgenerator_19ml105.h"    // linking the header file
#include <fstream>                      // importing necessary headers
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <iterator>
#include <time.h>

using namespace std;
void InsultGenerator::initialize(){
    ifstream sourceFile ("InsultsSource.txt");          // creating instream object with the arguement

    if (!(sourceFile.is_open())){                       // sourcefile can't open? Throw exception
        throw FileException();
    }
    else{                
        string line;
        this->col1.reserve(50);                         // reserving the space for the columns
        this->col2.reserve(50);
        this->col3.reserve(50);

        while(getline(sourceFile, line)){               // reading in the columns
            InsultGenerator::splitString(line);
        }
        sourceFile.close();
    }
    srand(time(NULL));                                  // setting seed for rand()
}// initialize()

// private helper function to split the string
void InsultGenerator::splitString(string input){
    int first = input.find('\t');
    int second = input.find('\t', first+1);                         // find the second occurrence of (tab)
    // pushing back to the object vectors
    this->col1.push_back(input.substr(0, first));                   // substr(pos, len)
    this->col2.push_back(input.substr(first+1, second-first-1));    
    this->col3.push_back(input.substr(second+1, input.length()-second+1));  
}// splitString()

string InsultGenerator::talkToMe(){
    // need to pick a random str from each vect(col1, col2, col3) and append it, return it
    string insult = "Thou " + this->col1[rand()%50] + " " + this->col2[rand()%50] + " " + this->col3[rand()%50];     // need to fill the indices with random ones everytime
    return insult;
}// talkToMe()

vector<string> InsultGenerator::generate(int num){
    if (num <= 0 || num > 10000){
        throw NumInsultsOutOfBounds();                                      // if the number is invalid, throw exception
    }
    else{
        set<string> resultSet;                                              // create set, this DS automatically checks for duplicates and maintains order
        for (int i=0; i < num; i++){
            while(1){
                // generate the insult
                if(resultSet.insert(InsultGenerator::talkToMe()).second){   // want the version of insert that returns a bool + iterator
                    break;                                                  // break out of loop upon successful insertion
                }
                else{}                                                      // duplicate exists, stay within the while until not a duplicate
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
        vector<string> results = InsultGenerator::generate(num);        // generate() will throw numInsultsOutOfBounds exception
        for (const auto &it : results){                                 // loop to write to the contents of the vector to the file, terminate with newline
            outFile << it << "\n";
        }
        outFile.close();                                                // close the output file
    }
}

char * FileException::what(){
    return "file exception";
}// what()

char * NumInsultsOutOfBounds::what(){
    return "the number of insults is out of bound";
}// what()
