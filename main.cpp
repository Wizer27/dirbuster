#include <iostream>
#include <vector>
#include <string>
#include <CLI/CLI.hpp>
#include <cpr/cpr.h>
#include <fstream>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;



int main(int argc,char** argv){
    CLI::App app{"Dirbuster"};
    std::string wordlist;
    std::string url;


    app.add_option("-u,--url",url,"Target url") -> required();
    app.add_option("-f,--file",wordlist,"Wordlist") -> required();

    CLI11_PARSE(app, argc, argv);

    std::ifstream file(wordlist);
    if(!file.is_open()){
        std::cout << "File not found" << std::endl;
        return 0;
    }

    std::string line;
    while(std::getline(file,line)){
        string url_to_test = url + line;
        auto response = cpr::Get(
            cpr::Url{url_to_test}
        );
        if(response.status_code != 404){
            std::cout << "===============" << std::endl;
            std::cout << "[+] URL: " <<  url_to_test << std::endl;
            std::cout << "[+] STATUS CODE: " << response.status_code << std::endl;
            std::cout << "===============" << std::endl;
        }

    };


    file.close();


    return 0;
}