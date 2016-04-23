//
//  main.cpp
//  socket_app
//
//  Created by Benjamin Rebertus on 4/22/16.
//  Copyright © 2016 Benjamin Rebertus. All rights reserved.
//

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
using namespace std;

int main(int argc, const char * argv[]) {
    bool serverMode;
    if (!strcmp("server", argv[1])){
        serverMode = true;
    } else if (!strcmp("client", argv[1])){
        serverMode = false;
    } else {
        cout << "Specify 'server' or 'client'\n";
        return 0;
    }
    
    auto sock = socket(AF_INET, SOCK_STREAM, 0);
    
    
    
    
    
    
    return 0;
}
