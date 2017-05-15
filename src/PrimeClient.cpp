/*
 * PrimeClient.cpp
 *
 *  Created on: May 11, 2017
 *      Author: gkiessling
 */

#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include "PrimeClient.h"

using namespace std;

PrimeClient::PrimeClient(const string &serverIpAddress, unsigned short serverPort)
: serverIpAddress(serverIpAddress), serverPort(serverPort)
{
}

string PrimeClient::sendPrimeTest(const string &n)
{
    return sendMessage(n);
}

string PrimeClient::sendDivisibleByOddRangeTest(const string &n, const string &start, const string &end)
{
    stringstream message;
    message << n << "," << start << "," << end;
    return sendMessage(message.str());
}

string PrimeClient::sendMessage(string message)
{
    int socketFd;
    struct sockaddr_in serverAddress;
    char buffer[2000];

    // Mark end of message with newline
    message += "\n";

    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd == -1)
    {
        return "Error: Could not create socket";
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(serverIpAddress.c_str());
    serverAddress.sin_port = htons(serverPort);

    if (::connect(socketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        strerror_r(errno, buffer, sizeof(buffer));
        return string("Error: connect failed - ") + buffer;
    }

    cout << "Connected to " << serverIpAddress << ":" << serverPort << endl;

    if (send(socketFd, message.c_str(), message.length(), 0) < 0)
    {
        strerror_r(errno, buffer, sizeof(buffer));
        return string("Error: send failed - ") + buffer;
    }

    int readSize;
    stringstream replyStream;

    while  ( (readSize = recv(socketFd, buffer, sizeof(buffer), 0)) > 0 )
    {
        buffer[readSize] = '\0';

        // Newline marks the end of the message
        if (buffer[readSize - 1] == '\n')
        {
            replyStream.write(buffer, readSize - 1);
            readSize = 0;
            break;
        }
        else
        {
            replyStream.write(buffer, readSize);
        }
    }

    shutdown(socketFd, SHUT_RD);
    close(socketFd);

    if (readSize == -1)
    {
        strerror_r(errno, buffer, sizeof(buffer));
        return string("Error: receive failed - ") + buffer;
    }

    return replyStream.str();
}
