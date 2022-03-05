#include <iostream>
#include <map>
#include <vector>
#include "./responder/responder.hpp"
#include "./responder/response.hpp"

#include <unistd.h>
// #include <csystem>
#include <fcntl.h>
int main()
{
    std::map<std::string, std::string> statusCode;


    std::vector<server_parser> servers;

    server_parser srv1;
    std::vector<std::string> _names;
    std::vector<std::string> _errorPages;
    srv1.setHost("0.0.0.0");
    srv1.setPort(8000);
    _names.push_back("server1");
    _names.push_back("server2");
    _names.push_back("server3");
    _errorPages.push_back("500");
    _errorPages.push_back("501");
    _errorPages.push_back("502");
    _errorPages.push_back("./50x.html");

    location_parser loc0, loc1, loc2, loc3;
    std::vector<std::string> _indexs;
    _indexs.push_back("index.html");
    _indexs.push_back("index.php");
    _indexs.push_back("index.htm");
    
    loc0.setLocationPath("/");
    loc0.setAutoIndex(false);
    loc0.setCGIPath("/Users/abahdir/goinfre/.brew/bin/php-cgi");
    loc0.setRootPath("/goinfre/abahdir/nginxTest/");

    loc1.setLocationPath("/home/");
    loc1.setAutoIndex(false);
    loc1.setCGIPath("/Users/abahdir/goinfre/.brew/bin/php-cgi");
    loc1.setRootPath("/goinfre/abahdir/nginxTest/");

    loc2.setLocationPath("/indesx.js");
    loc2.setAutoIndex(true);
    loc2.setCGIPath("/Users/abahdir/goinfre/.brew/bin/php-cgi");
    loc2.setRootPath("/goinfre/abahdir/nginxTest/");

    loc3.setLocationPath(".php");
    loc3.setAutoIndex(false);
    loc3.setCGIPath("/Users/abahdir/goinfre/.brew/bin/php-cgi");
    loc3.setRootPath("/goinfre/abahdir/nginxTest/");

    std::vector<location_parser> _locations;

    _locations.push_back(loc0);
    _locations.push_back(loc1);
    _locations.push_back(loc2);
    _locations.push_back(loc3);
    srv1.setLocations(_locations);
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

    request_parser req;
    req.setError("200");
    req.setServer(servers[0]);
    req.setMethode("GET");
    req.setPath("/home/index.js");
    req.setQueries("");
    req.setVersion("HTTP/1.1");
    req.setHeaders(headers);
    req.setBodyFile("./Makefile");

    Responder resp(req);

    // std::cout << resp.response();

    // system("cp -r ./default ~/webservconfig/");
    // system("rm -rf /tmp/webserv/*");
    // system("mkdir /tmp/webserv");

    std::cout << resp._indexOfPage("/", "/");

    // struct stat fileStat;
    // stat("/exam", &fileStat);

    // std::cout << (fileStat.st_mode & S_IWUSR) << std::endl;

    int fd = open("/goinfre/abahdir/webserv/Makefile", O_RDONLY);
    int readLen = 0;
    char x[1024];

    int sx = fcntl(fd, O_NONBLOCK);
    std::cout << sx;
    while ((readLen = read(fd, x, 1024)) > 0)
    {
        std::cout << x;
    }
    

    // std::cout << ("File Permissions: \t");
    // std::cout << ( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    // std::cout << ( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    // std::cout << ( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    // std::cout << ( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    // std::cout << ( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    // std::cout << ( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    // std::cout << ( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    // std::cout << ( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    // std::cout << ( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    // std::cout << ( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    // std::cout << ("\n\n");
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

