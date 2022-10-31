#ifndef fraction19ml105_H
#define fraction19ml105_H

#include <exception>
#include <string>
#include <iostream>
#include <vector>

class Fraction{
    private:
        int num;        // store the numerator
        int denom;      // store the denominator
        static int compGCD(int m, int n);                                                                       // helper to compute the GCD of 2 integers (COULD JUST USE gcd() from <algorithm>)
        static void reduceFraction(int numerator, int denominator);                                             // helper to reduce fraction to simplest terms
        friend std::vector<int> equalizeNumerators(const Fraction& thisFrac, const Fraction& otherFrac);        // returns vect with the fraction numerators
                                                                                                                // over a common denominator for comparison

    public:
        Fraction();                                     // default constructor, makes the 0 fraction
        Fraction(int numerator);                        // constructor w/ single arg
        Fraction(int numerator, int denominator);               
        int numerator();                                // accessor
        int denominator();                              // same
        Fraction& operator - ();                        // negation
        Fraction& operator ++ ();                       // preincrement
        Fraction operator ++ (int arb);                 // postincrement


    // using non-member friend overloading so that operators can handle situations when an input is not a Fraction()
    // just makes things easier

    // overloading the operators
    // iostream operators
    friend std::ostream& operator << (std::ostream& os, Fraction fraction);    // they all take objects of the fraction class
    friend std::istream& operator >> (std::istream& is, Fraction& fraction);    // they all take objects of the fraction class
    
    friend Fraction operator + (const Fraction& thisFrac, const Fraction& otherFrac);
    friend Fraction operator - (const Fraction& thisFrac, const Fraction& otherFrac);
    friend Fraction operator * (const Fraction& thisFrac, const Fraction& otherFrac);
    friend Fraction operator / (const Fraction& thisFrac, const Fraction& otherFrac);
    friend Fraction& operator += (Fraction& thisFrac, Fraction& otherFrac);
    // Unary operators must be member operators/ functions, have implicit this reference
    

    // comparison operators
    friend bool operator < (const Fraction& thisFrac, const Fraction& otherFrac);
    friend bool operator > (const Fraction& thisFrac, const Fraction& otherFrac);
    friend bool operator == (const Fraction& thisFrac, const Fraction& otherFrac);
    friend bool operator != (const Fraction& thisFrac, const Fraction& otherFrac);
    friend bool operator <= (const Fraction& thisFrac, const Fraction& otherFrac);
    friend bool operator >= (const Fraction& thisFrac, const Fraction& otherFrac);

};

class FractionException : public std::exception{// for exception handling
    public:
        char * what();
};

#endif