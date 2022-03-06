#include <iostream>
#include <map>
#include <vector>
#include "./responder/responder.hpp"
// #include "./responder/response.hpp"
#include "../parser/parser.hpp"


#include <unistd.h>
// #include <csystem>
#include <fcntl.h>

void printConfData(std::vector<server_parser> _srvs)
{
    if (_srvs.size() > 0)
    {
        std::cout << "\n## SERVERS ##\n" << std::endl;
        for(size_t i = 0; i < _srvs.size(); i++)
        {
            server_parser _srv = _srvs[i];
            std::cout << _srv.getHost() << std::endl;
            std::cout << _srv.getPort() << std::endl;
            std::cout << _srv.getRoot() << std::endl;
            std::vector<std::string> _srvNames = _srv.getNames();
            if (_srvNames.size() > 0)
                for(size_t i = 0; i < _srvNames.size(); i++)
                    std::cout << _srvNames[i] << std::endl;
            std::vector<std::string> _srvErrorPages = _srv.getErrorPages();
            if (_srvErrorPages.size() > 0)
                for(size_t i = 0; i < _srvErrorPages.size(); i++)
                    std::cout << _srvErrorPages[i] << std::endl;
            std::cout << _srv.getMaxSzie() << std::endl;

            //locations
            std::vector<location_parser> _locs = _srv._locations;
            if (_locs.size() > 0)
            {
                std::cout << "\n>>> LOCATIONS <<<\n" << std::endl;
                for(size_t i = 0; i < _locs.size(); i++)
                {
                    std::cout << _locs[i].getLocationPath() << std::endl;
                    std::vector<std::string> _locAcceptedReq = _locs[i].getAcceptedRequeasts();
                    if (_locAcceptedReq.size() > 0)
                        for(size_t i = 0; i < _locAcceptedReq.size(); i++)
                            std::cout << _locAcceptedReq[i] << std::endl;
                    std::cout << _locs[i].getAutoIndex() << std::endl;
                    std::cout << _locs[i].getCgiPath() << std::endl;
                    std::cout << _locs[i].getRootPath() << std::endl;
                    std::cout << _locs[i].getUploadPath() << std::endl;
                    std::cout << _locs[i].getRedirection().first << " --> " << _locs[i].getRedirection().second << std::endl;
                    std::vector<std::string> _locIndexs = _locs[i].getIndex();
                    if (_locIndexs.size() > 0)
                        for(size_t i = 0; i < _locIndexs.size(); i++)
                            std::cout << _locIndexs[i] << std::endl;
                    std::cout << ">>>>>>" << std::endl;
                }
                std::cout << ">>> END LOCATIONS <<<" << std::endl;
            }
            std::cout << "######" << std::endl;
        }
        std::cout << "### END SERVERS ###" << std::endl;
    }
}

int     main(int ac , char *av[])
{


    if (ac == 2)
    {
        try
        {
            parser *conf = new parser(av[1]);
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
            req.setServer(conf->_servers[0]);
            req.setMethode("GET");
            req.setPath("/home/index.js");
            req.setQueries("");
            req.setVersion("HTTP/1.1");
            req.setHeaders(headers);
            req.setBodyFile("./Makefile");

            Responder resp(req);
            // std::cout << resp._indexOfPage("/", "/");
            // printConfData(conf->_servers);


            delete conf;
        }
        catch(const char *str)
        {
            std::cerr << str << std::endl;
            exit(1);
        }
    }
    else
    {
        std::cerr << "Please provide a config file" << std::endl;
        return 1;
    }
    

    // std::cout << resp.response();

    // system("cp -r ./default ~/webservconfig/");
    // system("rm -rf /tmp/webserv/*");
    // system("mkdir /tmp/webserv");

    

    // struct stat fileStat;
    // stat("/exam", &fileStat);

    // std::cout << (fileStat.st_mode & S_IWUSR) << std::endl;

    // int fd = open("/goinfre/abahdir/webserv/Makefile", O_RDONLY);
    // int readLen = 0;
    // char x[1024];

    // int sx = fcntl(fd, O_NONBLOCK);
    // std::cout << sx;
    // while ((readLen = read(fd, x, 1024)) > 0)
    // {
    //     std::cout << x;
    // }
    

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

