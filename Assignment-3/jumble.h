#ifndef jumble_h
#define jumble_h

#include <exception>
#include <string>

class JumblePuzzle{
    private:
        void generatePuzzle();                  // generate a puzzle with given parameters
    public:
        JumblePuzzle();                         // default constructor
        JumblePuzzle(const JumblePuzzle &jp);   // copy constructor
        int difficulty;                         // values between 2-4
        std::string inputWord;                  // user input
};

class BadJumbleException : public std::exception{
    // exception handler
};

#endif