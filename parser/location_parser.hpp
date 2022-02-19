#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

class location_parser
{
    private :
        

    public :
        std::vector<std::string> accepted_requests;
        std::string location_path;
        std::string root_path;
        std::vector<std::string> index;
        std::string upload_path;
        std::string cgi_path;
        std::pair<int, std::string> redirection;
        bool auto_index;

};