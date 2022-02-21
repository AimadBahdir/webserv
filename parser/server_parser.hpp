#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

class server_parser
{
    private :

    public :
        std::string host;
        size_t port;
        std::vector<std::string> names;
        std::vector<std::string> error_pages;
       // std::vector<location> locations;
        int clientMaxBodySize;
};
