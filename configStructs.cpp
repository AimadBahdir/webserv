#include <iostream>
#include <map>
#include <vector>
#include <utility>

struct location
{
    std::vector<std::string> accepted_requests;
    std::string location_path;
    std::string root_path;
    std::vector<std::string> index;
    std::string upload_path;
    std::string cgi_path;
    std::pair<int, std::string> redirection;
    bool auto_index;
};

struct server
{
    std::string host;
    size_t port;
    std::vector<std::string> names;
    std::vector<std::string> error_pages;
    std::vector<location> locations;
    int clientMaxBodySize;
};
