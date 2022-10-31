#include "fraction_19ml105.h"
#include <exception>
#include <string>
#include <vector>

using namespace std;

// Fraction class implementation

Fraction::Fraction() : num(0), denom(1){}
Fraction::Fraction(int numerator) : num(numerator), denom(1){}
Fraction::Fraction(int numerator, int denominator){
    if (denominator == 0) throw FractionException();                    // trying to divide by 0
    else{
        int gcd = compGCD(abs(numerator), abs(denominator));            // wrap this into private helper function
        numerator = numerator/gcd;                                      // ^
        denominator = denominator/gcd;                                  // ^

        if (numerator < 0 && denominator < 0){                          // if both are negative, fraction is overall positive
            num = abs(numerator);
            denom = abs(denominator);
        }
        else if (denominator < 0){                              // negative denominator
            num = abs(numerator)*-1;                                    // otherwise one of them is negative
            denom = abs(denominator);                                   // either case, shift negative to the numerator
        }
        else{
            num = numerator;
            denom = denominator;
        }
    }
}

/*
void Fraction::reduceFraction(Fraction fraction){
    int gcd = compGCD(abs(fraction.num), abs(fraction.denom));            // wrap this into private helper function
    fraction.num = fraction.num/gcd;                                      // ^
    fraction.denom = fraction.denom/gcd;
}
*/

int Fraction::numerator(){
    return num;
}
int Fraction::denominator(){
    return denom;
}

int Fraction::compGCD(int n, int d){
    if (d <= n && n%d==0) return d;
    else if (n < d) return Fraction::compGCD(d, n);
    else return Fraction::compGCD(d, n%d);
}// compGCD()

// Operator overloads
ostream& operator << (ostream& os, Fraction fraction){
    os << fraction.numerator() << '/' << fraction.denominator();
    return os;
}

Fraction operator+(const Fraction& otherFrac) const{
    // need to call constructor 3
    int LCM = abs(this.denom * otherFrac.denom)/ Fraction::compGCD(this.denom, otherFrac.denom);    // works
    int top = (this.num * (LCM/denom)) + (otherFrac.num * (LCM/otherFrac.denom));
    Fraction result(top ,LCM);
    return result;
}

Fraction operator-(const Fraction& otherFrac){
    return this + -1*otherFrac; // call the overloaded multiplication func and the addition operators
}

Fraction operator * (const Fraction& otherFrac){
    return this / (1/otherFrac);
}

Fraction operator / (const Fraction& otherFrac){
    Fraction result(this.num * otherFrac.denom, this.denom * otherFrac.num);
    return result;
}

/*
Fraction operator - (){
    Fraction negatedFrac(-1*this.num, this.denom);
    return negatedFrac;
}
*/
// comparison operators

bool operator < (const Fraction& thisFrac, const Fraction& otherFrac){
    vector<int> numerators = equalizeNumerators(thisFrac, otherFrac);
    if (numerators[0] < numerators [1]) return true;
    else return false;
}


bool operator == (const Fraction& thisFrac, const Fraction& otherFrac){
    vector<int> numerators = equalizeNumerators(thisFrac, otherFrac);
    if (numerators[0] == numerators [1]) return true;
    else return false;
}

// Helper functions
vector<int> equalizeNumerators(const Fraction& thisFrac, const Fraction& otherFrac){
    vector<int> result;
    int LCM = abs(thisFrac.denom * otherFrac.denom)/ Fraction::compGCD(thisFrac.denom, otherFrac.denom);
    result.push_back(thisFrac.num * (LCM/thisFrac.denom));
    result.push_back(otherFrac.num * (LCM/otherFrac.denom));
    return result;
}

char * FractionException::what(){
    return "ERROR! division by 0!";
}