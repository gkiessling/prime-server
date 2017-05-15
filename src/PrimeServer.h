/*
 * PrimeServer.h
 *
 *  Created on: May 14, 2017
 *      Author: gkiessling
 */

#ifndef PRIMESERVER_H_
#define PRIMESERVER_H_

#include <string>
#include <vector>

#include "PrimeClient.h"

using namespace std;

class PrimeServer
{
public:
    PrimeServer(unsigned short serverPort);
    int start();
    void addAuxServer(const string &ipAddress, unsigned short port);

private:
    unsigned short serverPort;
    vector<PrimeClient> auxServers;
};


#endif /* PRIMESERVER_H_ */
