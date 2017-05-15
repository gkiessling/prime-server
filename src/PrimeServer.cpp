/*
 * PrimeServer.cpp
 *
 *  Created on: May 11, 2017
 *      Author: gkiessling
 */

#include <iostream>
#include <sstream>
#include <thread>

#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "PrimeServer.h"
#include "PrimeValidator.h"

using namespace std;

static void processConnection(int clientFd)
{
    int readSize;
    char buffer[2000];
    stringstream clientStream;
    PrimeValidator primeValidator;

    cout << "Connection accepted" << endl;

    while ( (readSize = recv(clientFd, buffer, sizeof(buffer), 0)) > 0 )
    {
        // Newline marks the end of the message
        if (buffer[readSize - 1] == '\n')
        {
            clientStream.write(buffer, readSize - 1);
            readSize = 0;
            break;
        }
        else
        {
            clientStream.write(buffer, readSize);
        }
    }

    string clientMessage(clientStream.str());
    cout << "Client request: " << clientMessage << endl;

    string reply(primeValidator.isPrime(clientMessage) ? "true\n" : "false\n");

    ::write(clientFd , reply.c_str(), reply.length());
    ::shutdown(clientFd, SHUT_WR);

    if (readSize == 0)
    {
        cout << "Client disconnected" << endl;
    }
    else if(readSize == -1)
    {
        perror("Receive failed");
    }
}

PrimeServer::PrimeServer(unsigned short serverPort)
: serverPort(serverPort)
{
}

int PrimeServer::start()
{
    int socketFd;
    int clientFd;
    int socketLen = sizeof(struct sockaddr_in);
    struct sockaddr_in serverAddress, clientAddress;

    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd == -1)
    {
        cerr << "Could not create socket" << endl;
        return -1;
    }
    cout << "Socket created" << endl;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(serverPort);

    if (::bind(socketFd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        perror("Bind failed");
        return -1;
    }
    cout << "Bind complete" << endl;

    ::listen(socketFd , 3);

    cout << "Waiting for incoming connections on port " << serverPort << endl;

    while ( (clientFd = ::accept(socketFd, (struct sockaddr *)&clientAddress, (socklen_t*)&socketLen)) )
    {
        if (clientFd < 0)
        {
            perror("Accept failed");
            continue;
        }

        // Better to use a thread pool, or even better, asynchronous IO.
        // But having one client thread per connection will suffice for this project.
        thread(processConnection, clientFd).detach();
    }

    return 0;
}

void PrimeServer::addAuxServer(const string &ipAddress, unsigned short port)
{
    auxServers.push_back(PrimeClient(ipAddress, port));
}

