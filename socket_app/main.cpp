//
//  main.cpp
//  socket_app
//
//  Created by Benjamin Rebertus on 4/22/16.
//  Copyright © 2016 Benjamin Rebertus. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <unistd.h>
using namespace std;

void server(int connect){
    string str;
    while(true){
        char buff;
        size_t bytesWritten = recv(connect, &buff, sizeof(buff), 0);
        cout << bytesWritten;
        cout << buff;
        if (buff == '\0') break;
        else str += buff;
    }
    cout << str;
}

void client(int connect){
    while (true) {
        string toSend;
        cout << "Enter message: ";
        getline(cin, toSend);
        toSend += '\0';
        cout << toSend;
        send(connect, toSend.c_str(), toSend.size(), 0);
    }
}


int main(int argc, const char * argv[]) {
    bool serverMode;
    if (argc < 2){
        cout << "Specify 'server' or 'client'\n";
        return 0;
    }
    if (!strcmp("server", argv[1])){
        serverMode = true;
    } else if (!strcmp("client", argv[1])){
        serverMode = false;
    } else {
        cout << "Specify 'server' or 'client'\n";
        return 0;
    }
    
    auto sock = socket(AF_INET, SOCK_STREAM, 0);
    
    int yes = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, 4);
    sockaddr_in addr; //structure will define how we connect
    addr.sin_family = AF_INET;
    if (serverMode){
        cout << "Starting server\n";
        
        addr.sin_port = htons(0);
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        
        ::bind(sock, (sockaddr*)&addr, sizeof(addr));
        
        listen(sock, 0);
        
        sockaddr_in addr;
        socklen_t len = sizeof(addr);
        getsockname(sock, (sockaddr*)&addr, &len);
        unsigned short port = ntohs(addr.sin_port);
        cout << "PORT: " << port << endl;
        
        while (true) {
            auto clientConnection = accept(sock, 0, 0);
            cout << "accepted conection";
            server(clientConnection);
        }
        
    } else {
        cout << "Client attempting connection..." << endl;
        addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        unsigned short portnum;
        cout << "Connect to port: ";
        cin >> portnum;
        string junk; //throw away the newline so we don't send it later
        getline(cin, junk);
        
        addr.sin_port = htons(portnum);

        cout << connect(sock, (sockaddr*)&addr, sizeof(addr));
        
        client(sock);

    }
    
    
    
    
    return 0;
}
