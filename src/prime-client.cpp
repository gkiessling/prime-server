/*
 * prime-client.cpp
 *
 *  Created on: May 14, 2017
 *      Author: gkiessling
 */

#include <iostream>

#include "PrimeClient.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Server IP address:port expected as first argument" << endl;
        return -1;
    }

    string serverAddress(argv[1]);
    auto delimiterPos = serverAddress.find(':');

    if (delimiterPos == string::npos)
    {
        cerr << "':' expected in server IP address:port argument" << endl;
        return -2;
    }

    string serverIpAddress(serverAddress.substr(0, delimiterPos));
    int serverPort(strtol(serverAddress.substr(delimiterPos + 1).c_str(), NULL, 0));

    if (serverPort <= 0 || serverPort > 65535)
    {
        cerr << "Port value in the range (0..65535] expected following ':' in first argument" << endl;
        return -3;
    }

    if (argc < 3)
    {
        cerr << "Expected number to test for primality as second argument" << endl;
        return -4;
    }

    string n(argv[2]);
    PrimeClient client(serverIpAddress, static_cast<unsigned short>(serverPort));

    cout << "Sending " << n << " to server " << serverIpAddress << ":" << serverPort << endl;
    string result = client.sendPrimeTest(n);

    if (result == "true" || result == "false")
    {
        cout << endl << "-------------------------------------------------------------------------" << endl;
        cout << endl << "Server returned result: " << n
                << (result == "true" ? " is " : " is not ")
                << "prime." << endl;
        return 0;
    }
    else
    {
        cerr << endl << "Error while communicating with server: " << result << endl;
        return 1;
    }
}



