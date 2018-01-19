/*
Copyright 2018 Trinh D.D. Nguyen

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __FRACTION_HPP__
#define __FRACTION_HPP__

#include <iostream>

class CFraction
{
public:
    // constructors
    CFraction(long nume = 0L, long denom = 1L);
    CFraction(const CFraction & rhs);

    // methods
    void set(long nume = 0L, long denom = 1L);
    CFraction reduce();
    bool fromString(std::string fraction);
    double value() const;

    // getters
    long getNumerator() const;
    long getDenominator() const;

    // overloads
    CFraction operator - ();                    // negate
    void operator = (const CFraction & rhs);    // assignment

    // type casters
    operator int() const;
    operator long() const;
    operator float() const;
    operator double() const;
    operator std::string() const;

    // input/output via iostream
friend std::ostream & operator << (std::ostream & os, const CFraction & obj);
friend std::istream & operator >> (std::istream & is, CFraction & obj);

    // binary relative operators
friend bool operator == (const CFraction & lhs, const CFraction & rhs);
friend bool operator != (const CFraction & lhs, const CFraction & rhs);
friend bool operator <= (const CFraction & lhs, const CFraction & rhs);
friend bool operator >= (const CFraction & lhs, const CFraction & rhs);
friend bool operator < (const CFraction & lhs, const CFraction & rhs);
friend bool operator > (const CFraction & lhs, const CFraction & rhs);

    // binary numerical operator
friend CFraction operator + (const CFraction & lhs, const CFraction & rhs);
friend CFraction operator - (const CFraction & lhs, const CFraction & rhs);
friend CFraction operator * (const CFraction & lhs, const CFraction & rhs);
friend CFraction operator * (const CFraction & lhs, int rhs);
friend CFraction operator * (const CFraction & lhs, long rhs);
friend CFraction operator * (int lhs, const CFraction & rhs);
friend CFraction operator * (long lhs, const CFraction & rhs);
friend CFraction operator / (const CFraction & lhs, const CFraction & rhs);

friend CFraction operator += (CFraction & lhs, const CFraction & rhs);
friend CFraction operator -= (CFraction & lhs, const CFraction & rhs);
friend CFraction operator *= (CFraction & lhs, const CFraction & rhs);
friend CFraction operator *= (CFraction & lhs, long rhs);
friend CFraction operator /= (CFraction & lhs, const CFraction & rhs);

    // TODO:
    // implement operator ++: F += 1
    // implement operator --: F -= 1

    static  bool autoReduce;    // auto fraction reduction flag
    static  char separator;     // fraction separator character

protected:
    // a fraction has this format: numerator/denominator
    long    numerator;
    long    denominator;
};

#endif
