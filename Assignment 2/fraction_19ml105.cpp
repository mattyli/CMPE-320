#include "fraction_19ml105.h"
#include <exception>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

// Fraction class implementation
Fraction::Fraction() : num(0), denom(1){}                               // default constructor, the 0 fraction
Fraction::Fraction(int numerator) : num(numerator), denom(1){}          // constructor with 1 arguement, the numerator
Fraction::Fraction(int numerator, int denominator){
    if (denominator == 0) throw FractionException();                    // trying to divide by 0
    else{
        int gcd = compGCD(abs(numerator), abs(denominator));           
        numerator = numerator/gcd;                                     
        denominator = denominator/gcd;            

        if (numerator < 0 && denominator < 0){                          // if both are negative, fraction is overall positive
            num = abs(numerator);
            denom = abs(denominator);
        }
        else if (denominator < 0){                                      // negative denominator
            num = abs(numerator)*-1;                                    // otherwise one of them is negative
            denom = abs(denominator);                                   // either case, shift negative to the numerator
        }
        else{
            num = numerator;                                            // negative numerator, positive denominator would fall through to here
            denom = denominator;                                        // can just set the fields
        }
    }
}

// helper functions

void Fraction::reduceFraction(int numerator, int denominator){
    int gcd = compGCD(abs(numerator), abs(denominator));            // wrap this into private helper function
    numerator= numerator/gcd;                                      // ^
    denominator = denominator/gcd;
}

vector<int> equalizeNumerators(const Fraction& thisFrac, const Fraction& otherFrac){
    vector<int> result;
    int LCM = abs(thisFrac.denom * otherFrac.denom)/ Fraction::compGCD(thisFrac.denom, otherFrac.denom);
    result.push_back(thisFrac.num * (LCM/thisFrac.denom));
    result.push_back(otherFrac.num * (LCM/otherFrac.denom));
    return result;
}// return the numerators of two fractions over a common denominator, do not need the denominator

int Fraction::compGCD(int n, int d){
    if (d <= n && n%d==0) return d;
    else if (n < d) return Fraction::compGCD(d, n);
    else return Fraction::compGCD(d, n%d);
}// compGCD()

// end helpers

// getter functions
int Fraction::numerator(){
    return num;
}
int Fraction::denominator(){
    return denom;
}

// end getters

// Operator overloads
ostream& operator << (ostream& os, Fraction fraction){
    os << fraction.num << '/' << fraction.denom;
    return os;
}

istream& operator >> (std::istream& is, Fraction& fraction){
    string in, temp;
    is >> in;
    stringstream instream(in);
    vector<int> fractionComponents;
    while(getline(instream, temp, '/')){
        fractionComponents.push_back(stoi(temp));               // use getline() to push the fraction components back
    }
    
    if(fractionComponents[1] == 0) throw FractionException();   // if denominator is 0, invalid fraction
    else{
        if (fractionComponents.size() < 2){                     // if only numerator, take numerator, denominator default = 1
            fraction.num = int(fractionComponents[0]);
            fraction.denom = 1;
        }
        else{
            Fraction::reduceFraction(fractionComponents[0], fractionComponents[1]);     // else, reduce the fraction
            fraction.num = int(fractionComponents[0]);                                  // initialize fraction fields to the reduced values 
            fraction.denom = int(fractionComponents[1]);
        }
    }   
    return is;                                                  // return the istream object
}

Fraction operator+(const Fraction& thisFrac, const Fraction& otherFrac){
    int LCM = abs(thisFrac.denom * otherFrac.denom)/ Fraction::compGCD(thisFrac.denom, otherFrac.denom);    // Compute the LCM, this becomes the new denominator
    int top = (thisFrac.num * (LCM/thisFrac.denom)) + (otherFrac.num * (LCM/otherFrac.denom));              // just need to do addition on the numerators
    Fraction result(top ,LCM);                                                                              // create new Fraction variable
    return result;
}

Fraction operator-(const Fraction& thisFrac, const Fraction& otherFrac){
    return thisFrac + -1*otherFrac;                                         // call the overloaded multiplication func and the addition operators
}

Fraction operator * (const Fraction& thisFrac, const Fraction& otherFrac){
    return thisFrac / (1/otherFrac);                                        // caling the overloaded division operator
}

Fraction operator / (const Fraction& thisFrac, const Fraction& otherFrac){
    return Fraction(thisFrac.num * otherFrac.denom, thisFrac.denom * otherFrac.num);    // simple cross multiplications
}

Fraction& Fraction::operator - (){
    num = -num;
    return *this;
}

Fraction& Fraction::operator ++ (){
    // preincrement
    num += denom;       // equivalent to adding 1/1
    return *this;

}

Fraction Fraction::operator ++ (int arb){
    Fraction tempvar = *this;
    ++*this;
    return tempvar;
}


Fraction& operator += (Fraction& thisFrac, Fraction& otherFrac){
    thisFrac = thisFrac + otherFrac;
    return thisFrac;
}

// comparison operators, will use the equalizeNumerators()
bool operator < (const Fraction& thisFrac, const Fraction& otherFrac){
    vector<int> numerators = equalizeNumerators(thisFrac, otherFrac);
    return (numerators[0] < numerators [1]);
}

bool operator > (const Fraction& thisFrac, const Fraction& otherFrac){
    vector<int> numerators = equalizeNumerators(thisFrac, otherFrac);
    return (numerators[0] > numerators [1]);
}

bool operator == (const Fraction& thisFrac, const Fraction& otherFrac){
    vector<int> numerators = equalizeNumerators(thisFrac, otherFrac);
    return (numerators[0] == numerators [1]);
}

bool operator != (const Fraction& thisFrac, const Fraction& otherFrac){
    vector<int> numerators = equalizeNumerators(thisFrac, otherFrac);
    return (numerators[0] != numerators [1]);
}

bool operator <= (const Fraction& thisFrac, const Fraction& otherFrac){
    vector<int> numerators = equalizeNumerators(thisFrac, otherFrac);
    return (numerators[0] <= numerators [1]);
}

bool operator >= (const Fraction& thisFrac, const Fraction& otherFrac){
    vector<int> numerators = equalizeNumerators(thisFrac, otherFrac);
    return (numerators[0] >= numerators [1]);
}
// end comparison operators

char * FractionException::what(){
    return "ERROR! division by 0!";
}