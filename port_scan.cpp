#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>


using namespace std;



string get_ip(string& domain){
    addrinfo hints{}, *res;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

   if (getaddrinfo(domain.c_str(), nullptr, &hints, &res) == 0) {
        sockaddr_in* addr = (sockaddr_in*)res->ai_addr;

        char ip[INET_ADDRSTRLEN];

        inet_ntop(AF_INET, &addr->sin_addr, ip, sizeof(ip));

        std::string ip_string = ip;
        freeaddrinfo(res);
        return ip_string;
    }
}

bool is_port_open(const string& ip,int port){
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){
        return false;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

    bool ok = connect(sock, (sockaddr*)&addr, sizeof(addr)) == 0;

    close(sock);
    return ok;
}

int main(){
    return 0;
}