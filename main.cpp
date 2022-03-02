#include <iostream>
#include <map>
#include <vector>
#include "./responder/responder.hpp"
#include "./responder/response.hpp"

#include <unistd.h>
// #include <csystem>

int main()
{
    std::map<std::string, std::string> statusCode;


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

    location loc0, loc1, loc2, loc3;
    loc0.location_path = "/";
    loc0.auto_index = false;
    loc0.cgi_path = "/Users/abahdir/goinfre/.brew/bin/php-cgi";
    loc0.index.push_back("index.html");
    loc0.index.push_back("index.php");
    loc0.index.push_back("index.htm");
    loc0.root_path = "/goinfre/abahdir/nginxTest/";

    loc1.location_path = "/home/";
    loc1.auto_index = false;
    loc1.cgi_path = "/Users/abahdir/goinfre/.brew/bin/php-cgi";
    loc1.index.push_back("index.html");
    loc1.index.push_back("index.php");
    loc1.index.push_back("index.htm");
    loc1.root_path = "/goinfre/abahdir/nginxTest/";

    loc2.location_path = "/indesx.js";
    loc2.auto_index = false;
    loc2.cgi_path = "/Users/abahdir/goinfre/.brew/bin/php-cgi";
    loc2.index.push_back("index.html");
    loc2.index.push_back("index.php");
    loc2.index.push_back("index.htm");
    loc2.root_path = "/goinfre/abahdir/nginxTest/";

    loc3.location_path = ".php";
    loc3.auto_index = false;
    loc3.cgi_path = "/Users/abahdir/goinfre/.brew/bin/php-cgi";
    loc3.index.push_back("index.html");
    loc3.index.push_back("index.php");
    loc3.index.push_back("index.htm");
    loc3.root_path = "/goinfre/abahdir/nginxTest/";

    srv1.locations.push_back(loc0);
    srv1.locations.push_back(loc1);
    srv1.locations.push_back(loc2);
    srv1.locations.push_back(loc3);
    servers.push_back(srv1);

    std::map<std::string, std::string> headers;

    headers["Host"] = "127.0.0.1";
    headers["Port"] = "8000";
    headers["Connection"] = "keep-alive";
    headers["Cache-Control"] = "max-age=0";
    headers["Upgrade-Insecure-Requests"] = "1";
    headers["User-Agent"] = "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/537.36 (KHTML] = like Gecko) Chrome/89.0.4389.114 Safari/537.36";
    headers["Accept"] = "text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9";
    headers["Sec-Fetch-Site"] = "cross-site";
    headers["Sec-Fetch-Mode"] = "navigate";
    headers["Sec-Fetch-User"] = "?1";
    headers["Sec-Fetch-Dest"] = "document";
    headers["Accept-Encoding"] = "gzip, deflate, br";
    headers["Accept-Language"] = "en-US,en;q=0.9";

    request req;
    req.error = "200";
    req.serv = servers[0];
    req.methode = "GET";
    req.path = "/home/index.js";
    req.queries = "";
    req.version = "HTTP/1.1";
    req.headers = headers;
    req.bodyFile = "";

    Responder resp(req);

    std::cout << resp.response();

    // system("cp -r ./default ~/webservconfig/");
    // system("rm -rf /tmp/webserv/*");
    // system("mkdir /tmp/webserv");

    // std::pair<bool, std::string> res;
    // while (true)
    // {
    //     res = resp.Read(1);
    //     std::cout << res.second;
    //     if (res.first)
    //         break;
    // }
    // std::cout << resp._indexOfPage("/goinfre/abahdir/nginxTest/", "/ok/") << std::endl;
    return (0);
}
