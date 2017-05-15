/*
 * PrimeClient.h
 *
 *  Created on: May 14, 2017
 *      Author: gkiessling
 */

#ifndef PRIMECLIENT_H_
#define PRIMECLIENT_H_

#include <string>

using namespace std;

class PrimeClient
{
public:
    PrimeClient(const string &serverIpAddress, unsigned short serverPort);
    string sendPrimeTest(const string &n);
    string sendDivisibleByOddRangeTest(const string &n, const string &start, const string &end);

private:
    string sendMessage(string message);

    string serverIpAddress;
    unsigned short serverPort;
};



#endif /* PRIMECLIENT_H_ */
