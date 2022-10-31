#ifndef fraction19ml105_H
#define fraction19ml105_H

#include <exception>
#include <string>
#include <iostream>
#include <vector>

class Fraction{
    private:
        int num;
        int denom;
        static int compGCD(int m, int n);          // helper to compute the GCD of 2 integers (COULD JUST USE gcd() from <algorithm>)
        //void reduceFraction(Fraction fraction);
        friend std::vector<int> equalizeNumerators(const Fraction& thisFrac, const Fraction& otherFrac);

    public:
        Fraction();                                     // default constructor, makes the 0 fraction
        Fraction(int numerator);
        Fraction(int numerator, int denominator);       
        int numerator();                                // accessor
        int denominator();                              // same

        // overloading the operators
        // iostream operators
        friend std::ostream& operator << (std::ostream& os, Fraction fraction);    // they all take objects of the fraction class
        
        Fraction operator + (const Fraction& otherFrac) const;
        Fraction operator - (const Fraction& otherFrac) const;
        Fraction operator * (const Fraction& otherFrac) const;
        Fraction operator / (const Fraction& otherFrac) const;
        //Fraction operator - () const;  // 

        // comparison operators
        friend bool operator < (const Fraction& thisFrac, const Fraction& otherFrac);
        friend bool operator == (const Fraction& thisFrac, const Fraction& otherFrac);

};

class FractionException : public std::exception{
    public:
        char * what();
};

#endif