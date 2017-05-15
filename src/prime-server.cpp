/*
 * prime-server.cpp
 *
 *  Created on: May 14, 2017
 *      Author: gkiessling
 */

#include <iostream>
#include <fstream>

#include "PrimeServer.h"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/istreamwrapper.h"

using namespace std;
using namespace rapidjson;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cerr << "Configuration file argument expected" << endl;
        return -1;
    }

    string configFilePath(argv[1]);
    ifstream configFile(configFilePath, ifstream::in);

    if (!configFile.is_open())
    {
        cerr << "Unable to open configuration file " << configFilePath << endl;
        return -3;
    }

    Document config;
    IStreamWrapper istreamWrapper(configFile);
    if (config.ParseStream(istreamWrapper).HasParseError())
    {
        cerr << "Unable to parse " << configFilePath << " as JSON: "
                << GetParseError_En(config.GetParseError()) << endl;
    }

    configFile.close();

    auto serverPortElem = config.FindMember("serverPort");

    if (serverPortElem == config.MemberEnd())
    {
        cerr << "No \"serverPort\" element found in " << configFilePath << endl;
        return -4;
    }

    int serverPort(serverPortElem->value.GetInt());

    if (serverPort <= 0 || serverPort > 65535)
    {
        cerr << "serverPort value in the range (0..65535] expected in " << configFilePath << endl;
        return -3;
    }

    PrimeServer server(serverPort);

    auto auxServersElem = config.FindMember("auxilliaryServers");

    if (auxServersElem != config.MemberEnd())
    {
        for (auto i = auxServersElem->value.MemberBegin();
                i != auxServersElem->value.MemberEnd();
                ++i)
        {
            string ipAddress(i->value["ipAddress"].GetString());
            int port(i->value["port"].GetInt());
            cout << "Adding auxiliary server " << ipAddress << ":" << port << endl;
            server.addAuxServer(ipAddress, static_cast<unsigned short>(port));
        }
    }

    cout << "PrimeServer starting..." << endl;

    server.start();
}




