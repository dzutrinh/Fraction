/*
Copyright 2018 Trinh D.D. Nguyen

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "fraction.hpp"

// private helpers for computing GCD and LCM of two integer operands

static long gcd(long a, long b)
{
    while (b)
    {
        long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

static long lcm(long a, long b)
{
    return  (a*b)/gcd(a, b);
}

bool CFraction::autoReduce = true;
char CFraction::separator = '/';

CFraction::CFraction(long nume, long denom)
{
    set(nume, denom);
}

CFraction::CFraction(const CFraction & rhs)
{
    if (*this != rhs)
    {
        this->numerator = rhs.numerator;
        this->denominator = rhs.denominator;
    }
}

void CFraction::set(long nume, long denom)
{
    if (denom == 0) // denominator must be non-zero
    {
        std::cout << "CFraction(): DIVISION BY ZERO" << std::endl;
        exit(0);
    }
    else
    if (nume == 0)  // we got a ZERO fraction here
    {
        this->numerator = 0L;
        this->denominator = 1L;
    }
    else
    {
        int sign = 1;       // sign of the fraction, assume positive

        if (nume < 0)       // if the numerator is negative
        {
            sign = -sign;   // sign is now negative
            nume = -nume;   // and negate the numerator
        }

        if (denom < 0)      // or if the denominator is negative
        {
            sign = -sign;   // sign is now negative
            denom = -denom; // and negate the denominator
        }

        // reduce the fraction if needed
        if (CFraction::autoReduce)
        {
            long u = gcd(nume, denom);
            nume /= u;
            denom /= u;
        }

        // initializes our fraction with proper sign, no reduction here
        this->numerator = sign * nume;
        this->denominator = denom;
    }
}

long CFraction::getNumerator() const
{
    return numerator;
}

long CFraction::getDenominator() const
{
    return denominator;
}

CFraction CFraction::reduce()
{
    long u = gcd(this->numerator, this->denominator);
    this->numerator /= u;
    this->denominator /= u;
    return *this;
}

bool CFraction::fromString(std::string fraction)
{
    size_t pos = fraction.find(CFraction::separator);
    long numerator, denominator;
    if (pos != std::string::npos)   // found the "/" character
    {
        try
        {
            // split the tokens
            std::string numerator_s = fraction.substr(0, pos);
            std::string denominator_s = fraction.substr(pos+1);

            // fix the missing tokens
            if (numerator_s.length() == 0)
            {
                numerator_s = "0";
            }
            if (denominator_s.length() == 0)
            {
                denominator_s = "1";
            }

            // conversion
            numerator = std::stol(numerator_s);
            denominator = std::stol(denominator_s);
        }
        catch (...)
        {
            // cannot convert the given string
            return false;
        }
        this->set(numerator, denominator);
        return true;
    }
    else
        if (fraction != "")
        {
            numerator = std::stol(fraction);
            denominator = 1L;
            this->set(numerator, denominator);
            return true;
        }
    return false;
}

double CFraction::value() const
{
    return double(*this);
}

CFraction CFraction::operator - ()
{
    return CFraction(-this->numerator, this->denominator);
}

void CFraction::operator = (const CFraction & rhs)
{
    if (*this != rhs)
    {
        this->numerator = rhs.numerator;
        this->denominator = rhs.denominator;
    }
}

CFraction::operator int() const
{
    return (int) this->numerator/this->denominator;
}

CFraction::operator long() const
{
    return (long) this->numerator/this->denominator;
}

CFraction::operator float() const
{
    return (float) this->numerator/this->denominator;
}

CFraction::operator double() const
{
    return (double) this->numerator/this->denominator;
}

CFraction::operator std::string() const
{
	std::string output = std::to_string(this->numerator);
    if (this->denominator != 1)
    {
        output += CFraction::separator;
        output += std::to_string(this->denominator);
    }
	return output;
}
std::ostream & operator << (std::ostream & os, const CFraction & obj)
{
    os << std::string(obj);
    return os;
}

std::istream & operator >> (std::istream & is, CFraction & fraction)
{
    std::string input;
    is >> input;
    fraction.fromString(input);
    return is;
}

bool operator == (const CFraction & lhs, const CFraction & rhs)
{
    return  (float)lhs == (float) rhs;
}

bool operator != (const CFraction & lhs, const CFraction & rhs)
{
    return  (float)lhs != (float) rhs;
}

bool operator >= (const CFraction & lhs, const CFraction & rhs)
{
    return  (float)lhs >= (float) rhs;
}

bool operator <= (const CFraction & lhs, const CFraction & rhs)
{
    return  (float)lhs <= (float) rhs;
}

bool operator > (const CFraction & lhs, const CFraction & rhs)
{
    return  (float)lhs > (float) rhs;
}

bool operator < (const CFraction & lhs, const CFraction & rhs)
{
    return  (float)lhs < (float) rhs;
}

CFraction operator + (const CFraction & lhs, const CFraction & rhs)
{
    long    u = lcm(lhs.denominator, rhs.denominator);
    CFraction result((lhs.numerator * (u/lhs.denominator)) +
                     (rhs.numerator * (u/rhs.denominator)), u);
    if (CFraction::autoReduce)
    {
        result.reduce();
    }
    return result;
}

CFraction operator - (const CFraction & lhs, const CFraction & rhs)
{
    long    u = lcm(lhs.denominator, rhs.denominator);
    CFraction result((lhs.numerator * (u/lhs.denominator)) -
                     (rhs.numerator * (u/rhs.denominator)), u);
    if (CFraction::autoReduce)
    {
        result.reduce();
    }
    return result;
}

CFraction operator * (const CFraction & lhs, const CFraction & rhs)
{
    CFraction result(lhs.numerator * rhs.numerator,
                     lhs.denominator * rhs.denominator);
    if (CFraction::autoReduce)
    {
        result.reduce();
    }
    return result;
}

CFraction operator * (const CFraction & lhs, int rhs)
{
    CFraction result(lhs.numerator * rhs, lhs.denominator);
    if (CFraction::autoReduce)
    {
        result.reduce();
    }
    return result;
}

CFraction operator * (const CFraction & lhs, long rhs)
{
    CFraction result(lhs.numerator * rhs, lhs.denominator);
    if (CFraction::autoReduce)
    {
        result.reduce();
    }
    return result;
}

CFraction operator * (int lhs, const CFraction & rhs)
{
    CFraction result(lhs * rhs.numerator, rhs.denominator);
    if (CFraction::autoReduce)
    {
        result.reduce();
    }
    return result;
}

CFraction operator * (long lhs, const CFraction & rhs)
{
    CFraction result(lhs * rhs.numerator, rhs.denominator);
    if (CFraction::autoReduce)
    {
        result.reduce();
    }
    return result;
}

CFraction operator / (const CFraction & lhs, const CFraction & rhs)
{
    CFraction result(lhs.numerator * rhs.denominator,
                     lhs.denominator * rhs.numerator);
    if (CFraction::autoReduce)
    {
        result.reduce();
    }
    return result;
}

CFraction operator += (CFraction & lhs, const CFraction & rhs)
{
    CFraction tmp = lhs + rhs;
    lhs = tmp;
    return lhs;
}

CFraction operator -= (CFraction & lhs, const CFraction & rhs)
{
    CFraction tmp = lhs - rhs;
    lhs = tmp;
    return lhs;
}

CFraction operator *= (CFraction & lhs, const CFraction & rhs)
{
    CFraction tmp = lhs * rhs;
    lhs = tmp;
    return lhs;
}

CFraction operator *= (CFraction & lhs, long rhs)
{
    CFraction tmp = lhs * rhs;
    lhs = tmp;
    return lhs;
}

CFraction operator /= (CFraction & lhs, const CFraction & rhs)
{
    CFraction tmp = lhs / rhs;
    lhs = tmp;
    return lhs;
}
