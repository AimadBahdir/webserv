#include <iostream>
#include <map>
#include <vector>
#include "./responder/responder.hpp"
#include "./responder/response.hpp"

#include <unistd.h>
int main()
{
    std::map<std::string, std::string> statusCode;


    std::map<std::string, std::string> requestData;

    requestData.insert(std::make_pair("Error", "300"));
    requestData.insert(std::make_pair("Methode", "GET"));
    requestData.insert(std::make_pair("URI", "/Users/abahdir/Desktop/webserv/Makefile"));
    requestData.insert(std::make_pair("Version", "HTTP/3"));
    requestData.insert(std::make_pair("Queries", "requestData"));
    ////////////////
    requestData.insert(std::make_pair("Host", "127.0.0.1"));
    requestData.insert(std::make_pair("Port", "8000"));
    requestData.insert(std::make_pair("Connection", "keep-alive"));
    requestData.insert(std::make_pair("Cache-Control", "max-age=0"));
    requestData.insert(std::make_pair("Upgrade-Insecure-Requests", "1"));
    requestData.insert(std::make_pair("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/89.0.4389.114 Safari/537.36"));
    requestData.insert(std::make_pair("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9"));
    requestData.insert(std::make_pair("Sec-Fetch-Site", "cross-site"));
    requestData.insert(std::make_pair("Sec-Fetch-Mode", "navigate"));
    requestData.insert(std::make_pair("Sec-Fetch-User", "?1"));
    requestData.insert(std::make_pair("Sec-Fetch-Dest", "document"));
    requestData.insert(std::make_pair("Accept-Encoding", "gzip, deflate, br"));
    requestData.insert(std::make_pair("Accept-Language", "en-US,en;q=0.9"));
    ///////////////
    requestData.insert(std::make_pair("body", "/body"));

    std::vector<server> servers;

    server srv1;
    srv1.host = "0.0.0.0";
    srv1.port = "8000";
    srv1.names.push_back("server1");
    srv1.names.push_back("server2");
    srv1.names.push_back("server3");
    srv1.error_pages.push_back("500");
    srv1.error_pages.push_back("501");
    srv1.error_pages.push_back("502");
    srv1.error_pages.push_back("./50x.html");

    location loc1;
    loc1.location_path = "/home";
    loc1.auto_index = false;
    loc1.cgi_path = "/Users/etc/cgi";
    loc1.index.push_back("index.html");
    loc1.index.push_back("index.htm");
    loc1.root_path = "/Users/home/";

    location loc2;
    loc2.location_path = "/about";
    loc2.auto_index = true;
    loc2.cgi_path = "/Users/etc/cgi";
    loc2.index.push_back("index.html");
    loc2.index.push_back("index.htm");
    loc2.root_path = "/Users/about/";

    srv1.locations.push_back(loc1);
    srv1.locations.push_back(loc2);
    servers.push_back(srv1);

    // RSP::Responder r(servers[0]);

    // RSP::Response resp = r.Respond(requestData);
    // std::pair<bool, std::string> res;
    // while (true)
    // {
    //     res = resp.Read(1);
    //     std::cout << res.second;
    //     if (res.first)
    //         break;
    // }

    return (0);
}