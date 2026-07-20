#include <iostream>
#include <vector>
#include <string>
#include <CLI/CLI.hpp>

using namespace std;


int main(int argc,char** argv){
    CLI::App app{"Dirbuster"};
    std::string wordlist;
    std::string url;


    app.add_option("-u,--url",url,"Target url") -> required();
    app.add_option("-f,--file",wordlist,"Wordlist") -> required();

    CLI11_PARSE(app, argc, argv);

    std::cout << "URL: " << url << '\n';
    std::cout << "Wordlist: " << wordlist << '\n';
    return 0;
}