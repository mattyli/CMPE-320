#ifndef IG19ml105_H
#define IG19ml105_H
#include <exception>
#include <vector>
#include <string>

// header file written by matthew li
// need to implement the class here

class InsultGenerator{
    private:
    //void splitString(std::string input, std::vector<std::string>& col1, std::vector<std::string>& col2, std::vector<std::string>& col3);
    void splitString(std::string input);
    std::vector<std::string> col1;
    std::vector<std::string> col2;
    std::vector<std::string> col3;

    public:
    void initialize();             
    std::string talkToMe();                             // returns a SINGLE randomly generated insult
    std::vector<std::string> generate(int num);         // should call talkToMe()
    void generateAndSave(std::string filename, int num);     // should call generate()
};

// file exception, extends the parent std::exception
class FileException : public std::exception {
    public:
    char * what();          // overriding the parent method
};

class NumInsultsOutOfBounds : public std::exception{
    public:
    char * what();
};


#endif
