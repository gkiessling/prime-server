/*
 * PrimeServer.cpp
 *
 *  Created on: May 11, 2017
 *      Author: gkiessling
 */

#include <iostream>
#include <sstream>
#include <vector>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

static const string responseHeader = "HTTP/1.1 200 OK\r\n"
    "Content-Type: application/json; charset=utf-8\r\n"
    "Connection: close\r\n"
    "Content-Length: ";

class PrimeServer
{
public:
    int start()
    {
        int socketFd;
        int clientFd;
        int socketLen = sizeof(struct sockaddr_in);
        int readSize;
        struct sockaddr_in server , client;
        char clientMessage[2000];

        socketFd = socket(AF_INET , SOCK_STREAM , 0);
        if (socketFd == -1)
        {
            cerr << "Could not create socket" << endl;
            return -1;
        }
        cout << "Socket created" << endl;

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(8080);

        if (::bind(socketFd, (struct sockaddr *)&server , sizeof(server)) < 0)
        {
            perror("Bind failed");
            return -1;
        }
        cout << "Bind complete" << endl;

        ::listen(socketFd , 3);

        cout << "Waiting for incoming connections..." << endl;

        clientFd = ::accept(socketFd, (struct sockaddr *)&client, (socklen_t*)&socketLen);
        if (clientFd < 0)
        {
            perror("Accept failed");
            return -1;
        }
        cout << "Connection accepted" << endl;

        //Receive a message from client
        while ( (readSize = recv(clientFd, clientMessage, sizeof(clientMessage), 0)) > 0 )
        {
            //Send the message back to client
            cout << "Request:" << endl << clientMessage << endl;
            std::string message(makeResponse("{ \"result\" : 12345 }"));
            ::write(clientFd , message.c_str(), message.length());
            cout << "Response:" << endl << message << endl;
        }

        if (readSize == 0)
        {
            cout << "Client disconnected" << endl;
        }
        else if(readSize == -1)
        {
            perror("Receive failed");
        }

        return 0;
    }

private:

    string makeResponse(string message)
    {
        stringstream result;
        result << responseHeader
                << (message.length())
                << "\r\n\r\n" << message;
        return result.str();
    }
};

int main(int argc, char *argv[])
{
    cout << "PrimeServer starting..." << endl;

    PrimeServer server;
    server.start();
}

