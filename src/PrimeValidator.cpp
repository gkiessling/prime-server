/*
 * PrimeValidator.cpp
 *
 *  Created on: May 11, 2017
 *      Author: gkiessling
 */
#include <climits>
#include <cmath>

#include "PrimeValidator.h"
#include "InfInt.h"

bool PrimeValidator::isPrime(unsigned long long n)
{
    if (n == 2 || n == 3)
    {
        return true;
    }

    // Some easy checks for non-prime
    // * 0
    // * 1
    // * All even numbers
    if (n < 2 || !(n & 1))
    {
        return false;
    }

    unsigned long long end = static_cast<unsigned long long>(sqrt(n));

    for (unsigned long long i = 3; i <= end; i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

bool PrimeValidator::isPrime(InfInt n)
{
    if (n <= ULLONG_MAX)
    {
        return isPrime(n.toUnsignedLongLong());
    }

    if (n % 2 == 0)
    {
        return false;
    }

    InfInt end = n.intSqrt();

    for (InfInt i = 3; i <= end; i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

bool PrimeValidator::isPrime(const string &s)
{
    char last = s[s.length()];

    // Some easy checks for non-prime
    // * Even numbers
    // * Numbers divisible by 5
    if (!(last & 1) || last == 5)
    {
        return false;
    }

    // Check for divisibility by 3
    long long sum = last;
    for (long long i = s.length() - 2; i >= 0; --i)
    {
        sum += s[i];
    }
    if (sum % 3 == 0)
    {
        return false;
    }

    try
    {
        InfInt n(s);

        try
        {
            unsigned long long l = n.toUnsignedLongLong();

            return isPrime(l);
        }
        catch (const InfIntException &e)
        {

        }
    }
    catch (const InfIntException &e)
    {
        return false;
    }

    return false;
}

