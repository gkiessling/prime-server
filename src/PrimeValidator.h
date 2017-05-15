/*
 * PrimeValidator.h
 *
 *  Created on: May 11, 2017
 *      Author: gkiessling
 */

#ifndef PRIMEVALIDATOR_H_
#define PRIMEVALIDATOR_H_

#include <string>

class InfInt;

using namespace std;

class PrimeValidator
{
public:
    bool isPrime(unsigned long long n);
    bool isPrime(const InfInt &n);
    bool isPrime(const string &s);
    bool isPrime(const char *s) { return isPrime(string(s)); }
};



#endif /* PRIMEVALIDATOR_H_ */
