#include <iostream>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string>
#include <CLI/CLI.hpp>

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

int main(int argc,char** argv){
    CLI::App app("port_scan");
    std::string domain;

    app.add_option("-d,--domain",domain,"Domain to scan.") -> required();

    CLI11_PARSE(app,argc,argv);


    string& domain_link = domain;

    string domain_ip = get_ip(domain_link);

    string& ip_link = domain_ip;
    
    const int port_amount = 65700;

    for(int i  = 0;i <= port_amount;i++){

        bool result_scan = is_port_open(ip_link,i);
        if(resuly_scan){
            std::cout << "PORT" << std::endl;
            std::cout << i << std::endl;
        }
    }

    std::cout << "Scanned " + port_amount.to_string() + " ports" << std::endl;
    return 0;

}