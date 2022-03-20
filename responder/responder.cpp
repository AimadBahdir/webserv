#include "./responder.hpp"
#include <fcntl.h>
#include <unistd.h>

#ifndef WEBDEFAULT
    #define WEBDEFAULT "/goinfre/abahdir/webservConf"
#endif

Responder::Responder(request_parser req, server_parser serv) : _request(req), _server(serv), _reqPath(req.getPath()), _statusCode("200"), _rootPath(WEBDEFAULT), _REDIRECT(false), _UPLOAD(false), _CGI(false)
{
    struct stat _fstat;
    if (stat(std::string(this->_rootPath+"/default").c_str(), &_fstat) != 0 
     && stat("./default", &_fstat) == 0 && S_ISDIR(_fstat.st_mode))
        system(std::string("cp -r ./default "+this->_rootPath).c_str());
}

Responder::Responder(Responder const & r) { (*this) = r; }

Responder& Responder::operator=(Responder const & r)
{
    this->_request = r._request;
    this->_location = r._location;
    this->_server = r._server;
    this->_statusCode = r._statusCode;
    return (*this);
}

bool    Responder::_errorsChecker(void)
{
    std::map<std::string, std::string> _headers = this->_request.getHeaders();
    if ( this->_request.getMethode().empty() || this->_request.getPath().empty() || this->_request.getVersion().empty()
    || (this->_server.getMaxSzie() > 0 && this->_server.getMaxSzie() < (int)this->_getFileLength(this->_request.getBodyFile()))
    || (_headers.find("Content-Length") != _headers.end() && _headers.find("Transfer-Encoding") != _headers.end())
    || (_headers.find("Host") == _headers.end()))
    {
        this->_statusCode = "400";
        return false;
    }
    if (this->_request.getMethode().empty())
    {
        this->_statusCode = "405";
        return false;
    }
    if (this->_request.getMethode().compare("GET") != 0
        && this->_request.getMethode().compare("POST") != 0
        && this->_request.getMethode().compare("DELETE") != 0)
    {
        this->_statusCode = "501";
        return false;
    }
    if (this->_request.getVersion().compare("1.1") != 0)
    {
        this->_statusCode = "505";
        return false;
    }
    return true;
}

Responder::RESPONSE_DATA Responder::response(void)
{
    if (this->_errorsChecker())
    {
        this->_setLocation(this->_request.getPath(), this->_server._locations);
        this->_setRootPath(this->_request.getPath());
        this->_prepareResponse();
    }
    return (this->_generateResponse());
}

size_t  Responder::_getFileLength(std::string _fpath)
{
    std::ifstream _file;
    size_t length;

    _file.open (_fpath.c_str(), std::ios::binary);
    _file.seekg (0, std::ios::end);
    length = _file.tellg();
    _file.close();
    return (length);
}

void    Responder::_setRootPath(std::string _path)
{
    if(!this->_location.getLocationPath().empty()
    && !this->_location.getRootPath().empty())
        this->_rootPath = this->_trimPath(this->_location.getRootPath() + "/" + _path);
    else if (!this->_server.getRoot().empty())
        this->_rootPath = this->_trimPath(this->_server.getRoot() + "/" + _path);
    else
    {
        this->_rootPath = WEBDEFAULT;
        this->_rootPath = this->_trimPath(this->_rootPath + "/" + _path);
    }
}

bool    Responder::_setIndex(std::string _index)
{
    struct stat _fstats;

    this->_indexPath = this->_rootPath;
    this->_indexPath += "/" + this->_location.getLocationPath();
    this->_indexPath += "/" + _index;
    this->_indexPath = this->_trimPath(this->_indexPath);
    if (stat(this->_indexPath.c_str(), &_fstats) == 0)
    {
        this->_rootPath = this->_trimPath(this->_rootPath + "/" + _index);
        this->_indexPath.clear();
        if (this->_setLocation(this->_trimPath(this->_request.getPath() + "/" + _index), this->_server._locations))
            this->_prepareResponse();
        this->_statusCode = "200";
        return true;
    }
    else
        this->_indexPath.clear();
    return false;
}

bool    Responder::_setIndexs(void)
{
    std::vector<std::string> _indexs = this->_location.getIndex();
    if (_indexs.size() == 0 && this->_setIndex("index.html"))
    {
        this->_indexPath = this->_rootPath;
        return (true);
    }
    for (size_t i = 0; i < _indexs.size(); i++)
        if (this->_setIndex(_indexs[i]))
            return (true);
    return (false);
}

void    Responder::_prepareResponse(void)
{
    struct stat _fstats;
    if (!this->_location.getLocationPath().empty())
    {
        if (!this->_location.getRedirection().first.empty())
        {
            this->_REDIRECT = true;
            this->_statusCode = this->_location.getRedirection().first;
            return;
        } else if (!this->_location.getUploadPath().empty()
        && this->_request.getMethode().compare("POST") == 0)
        {
            this->_UPLOAD = true;
            this->_statusCode = "200";
        }
        else if (!this->_location.getCgiPath().empty())
        {
            this->_CGI = true;
            this->_statusCode = "200";
            return;
        }
        else if (this->_setIndexs())
            this->_statusCode = "200";
        else if (this->_location.getAutoIndex())
            this->_statusCode = "200";
        else
            this->_statusCode = "403";
    }
    if (stat(this->_rootPath.c_str(), &_fstats) == 0)
    {
        if (S_ISDIR(_fstats.st_mode))
        {
            if(open(this->_rootPath.c_str(), O_RDONLY) == -1)
                this->_statusCode = "403";
            else
                this->_setIndexs();
        }
        else
        {
            if (!this->_location.getLocationPath().empty())
            {
                if (!this->_location.getRedirection().first.empty())
                {
                    this->_REDIRECT = true;
                    this->_statusCode = this->_location.getRedirection().first;
                    return;
                } else if (!this->_location.getUploadPath().empty()
                && this->_request.getMethode().compare("POST") == 0)
                {
                    this->_UPLOAD = true;
                    this->_statusCode = "200";
                    return;
                }
                else if(!this->_location.getCgiPath().empty())
                {
                    this->_CGI = true;
                    this->_statusCode = "200";
                    return;
                }
            }
            this->_indexPath = this->_rootPath;
            this->_statusCode = "200";
        }
    }
    else
    {
        if (errno == 2)
            this->_statusCode = "404";
        else
            this->_statusCode = "403";
    }
}

std::string Responder::_getDateTime(bool _fileName = false)
{
    time_t _now = time(0);

    if (!_fileName)
    {
        struct tm dt = *gmtime(&_now);
        char dateBuffer[96];
        std::strftime(dateBuffer, sizeof(dateBuffer), "%a, %d %b %Y %H:%M:%S %Z", &dt);
        return (std::string(dateBuffer));
    }
    else
    {
        struct timeval _ms;
        std::stringstream _res;
        _res << "WSRSP" << (_now + _ms.tv_usec);
        return (_res.str());
    }
}

Responder::RESPONSE_DATA Responder::_redirectResponse(std::string _stcode, std::string _redirectPath)
{
    std::stringstream _headers;
    this->_statusCode = _stcode;
    std::string _respath = this->_creatFile(_redirectPath, ".txt");
    _headers << this->_generateHeaders(_respath);
    std::vector<std::string> _redirectCodes;
    _redirectCodes.push_back("301");
    _redirectCodes.push_back("302");
    _redirectCodes.push_back("303");
    _redirectCodes.push_back("307");
    _redirectCodes.push_back("308");
    if (std::find(_redirectCodes.begin(), _redirectCodes.end(), _stcode) != _redirectCodes.end())
        _headers << "Location: " << _redirectPath << "\r\n";
    return (std::make_pair(_headers.str()+"\r\n", _respath));
}

Responder::RESPONSE_DATA Responder::_generateResponse(void)
{
    if (this->_REDIRECT)
        return (this->_redirectResponse(this->_location.getRedirection().first, this->_location.getRedirection().second));
    else if (this->_UPLOAD)
        return (this->_uploadFile());
    else if (this->_CGI)
        return (this->_cgiResponse());
    else 
        return (this->_staticResponse());
}

std::string Responder::_toUpper(const char* _str)
{
    std::string _newStr;
    for(size_t i = 0; i < strlen(_str); i++)
    {
        if(_str[i] == '-')
            _newStr += '_';
        else
            _newStr += std::toupper(_str[i]);
    }
    return (_newStr);
}

char**  Responder::_EnvarCGI()
{
    std::map<std::string, std::string> _headers = this->_request.getHeaders();
    char** _envars = (char**)malloc((_headers.size() + 8) * sizeof(char *));
    _envars[_headers.size() + 7] = NULL;
    std::map<std::string, std::string>::iterator _it;
    size_t i = 0;

    _envars[i++] = strdup(std::string("REQUEST_METHOD="+this->_request.getMethode()).c_str());
    _envars[i++] = strdup(std::string("QUERY_STRING="+this->_request.getQueries()).c_str());
    std::vector<std::string> _srvNames = this->_server.getNames();
    if (_srvNames.size() > 0)
        _envars[i++] = strdup(std::string("SERVER_NAME="+_srvNames[0]).c_str());
    else
        _envars[i++] = strdup("SERVER_NAME=127.0.0.1");

    if  (!this->_indexPath.empty())
    {
        _envars[i++] = strdup(std::string("SCRIPT_FILENAME="+this->_indexPath).c_str());
        _envars[i++] = strdup(std::string("SCRIPT_NAME="+this->_indexPath.substr(this->_indexPath.find_last_of("/") + 1)).c_str());
    }
    else
    {
        _envars[i++] = strdup(std::string("SCRIPT_FILENAME="+this->_rootPath).c_str());
        _envars[i++] = strdup(std::string("SCRIPT_NAME="+this->_rootPath.substr(this->_rootPath.find_last_of("/") + 1)).c_str());
    }
    _envars[i++] = strdup("SERVER_SOFTWARE=webserv/1.0.0");
    _envars[i++] = strdup("REDIRECT_STATUS=200");
    for (_it = _headers.begin(); _it != _headers.end(); _it++)
    {
        if (std::string("CONTENT_TYPE").compare(this->_toUpper(_it->first.c_str())) == 0)
            _envars[i++] = strdup(std::string("CONTENT_TYPE="+_it->second).c_str());
        else if (std::string("CONTENT_LENGTH").compare(this->_toUpper(_it->first.c_str())) == 0)
            _envars[i++] = strdup(std::string("CONTENT_LENGTH="+_it->second).c_str());
        else if (std::string("COOKIE").compare(this->_toUpper(_it->first.c_str())) == 0)
            _envars[i++] = strdup(std::string("HTTP_COOKIE="+_it->second).c_str());
        else if (std::string("USER_AGENT").compare(this->_toUpper(_it->first.c_str())) == 0)
            _envars[i++] = strdup(std::string("HTTP_USER_AGENT="+_it->second).c_str());
        else
            _envars[i++] = strdup(std::string("HTTP_"+this->_toUpper(_it->first.c_str())+"="+_it->second).c_str());
    }
    return (_envars);
}

void Responder::_setCGIResponseFile(std::string _path)
{
    int _outfd = open(_path.c_str(), O_CREAT | O_RDWR , 0400);
    int _infd = open(this->_request.getBodyFile().c_str(), O_RDONLY);
    if (_infd == -1)
        _infd = STDIN_FILENO;
    char** _cmd = (char **)malloc(3 * sizeof(char*));
    _cmd[0] = strdup(this->_location.getCgiPath().c_str());
    _cmd[1] = strdup(this->_indexPath.c_str());
    _cmd[2] = NULL;

    int _pid = fork();
    if (_pid == -1)
        this->_statusCode = "500";
    else if (_pid == 0)
    {
        if (dup2(_outfd, STDOUT_FILENO) == -1)
            exit(1);
        if (dup2(_infd, STDIN_FILENO) == -1)
            exit(1);
        if(execve(*_cmd, _cmd, _EnvarCGI()) == -1)
        {
            this->_statusCode = "500";
            close(_infd);
            close(_outfd);
            exit(errno);
        }
        close(_infd);
        close(_outfd);
        exit(0);
    }
    else
    {
        waitpid(_pid, 0, 0);
        if (_infd != -1)
            close(_infd);
        close(_outfd);
    }
}

Responder::RESPONSE_DATA Responder::_cgiResponse(void)
{
    std::stringstream _headers, _cgiHeaders;
    std::ifstream _file;
    std::string _line;

    if (this->_indexPath.empty())
        this->_indexPath = this->_rootPath;

    std::string _path = std::string("/tmp/"+_getDateTime(true));
    this->_setCGIResponseFile(_path);
    _file.open(_path, std::ios::in);
    size_t _len = 0;
    if (_file.is_open())
    {
        while (std::getline(_file, _line))
        {
            std::string _status =  _line.substr(0, std::string("Status: ").length());
            if (_status.compare("Status: ") == 0)
            {
                this->_statusCode = _line.substr(std::string("Status: ").length(), 3);
                continue;
            }
            if (_line.compare("\r") == 0 || _line.find(": ") == std::string::npos)
            {
                _file.close();
                break;
            }
            _len++;
            _cgiHeaders << _line << "\n";
        }
        std::stringstream _cmd;
        if (_len > 0)
            _cmd << "sed -e '1," << _len << "d' <" << _path << " > " << _path << "_";
        else
            _cmd << "cat < " << _path << " > " << _path << "_";
        system(_cmd.str().c_str());
    }
    _headers << this->_generateHeaders("");
    if (!_cgiHeaders.str().empty())
        _headers << _cgiHeaders.str();
    _headers << "Content-Length: "<< this->_getFileLength(_path+"_") <<"\r\n";
    return (std::make_pair(_headers.str()+"\n\r", std::string(_path+"_")));
}

std::string Responder::_generateHeaders(std::string _responseFILE = "")
{
    std::stringstream _responseHeaders;
    std::map<std::string, std::string> _headers = this->_request.getHeaders();

    _responseHeaders << "HTTP/1.1 " << this->_statusCode << " " << this->_getError(this->_statusCode) << "\r\n";
    _responseHeaders << "Server: webserv/1.0.0\r\n";
    _responseHeaders << "Date: "<< this->_getDateTime() <<"\r\n";
    if (_headers.find("Connection") != _headers.end())
        _responseHeaders << "Connection: " << _headers.find("Connection")->second << "\r\n";
    if (!_responseFILE.empty())
    {
        _responseHeaders << "Content-Length: "<< this->_getFileLength(_responseFILE) <<"\r\n";
        _responseHeaders << "Content-Type: " << this->_getMimeType(_responseFILE, false) << "\r\n";
    }
    return (_responseHeaders.str());
}

Responder::RESPONSE_DATA Responder::_staticResponse(void) 
{
    std::stringstream _response;
    if (this->_request.getMethode().compare("DELETE") == 0)
        this->_statusCode = "405";
    if (this->_statusCode.compare("200") != 0)
        return (this->_errorPagesChecker());
    else if (!this->_indexPath.empty())
    {
        if (this->_request.getMethode().compare("POST") == 0)
        {
            this->_statusCode = "405";
            return (this->_staticResponse());
        }
        return (std::make_pair(std::string(_generateHeaders(this->_indexPath)+"\r\n"), this->_indexPath));
    }
    else
    {
        if (this->_request.getMethode().compare("POST") == 0)
        {
            this->_statusCode = "403";
            return (this->_staticResponse());
        }
        std::string _path = this->_indexOfPage(this->_rootPath, this->_reqPath);
        return (std::make_pair(std::string(_generateHeaders(_path)+"\r\n"), _path));
    }
}

Responder::RESPONSE_DATA Responder::_uploadFile(void) 
{
    
    int _fd  = open(this->_location.getUploadPath().c_str(), O_RDONLY);
    if (_fd == -1)
    {
        this->_statusCode = "500";
        close(_fd);
        return (this->_staticResponse());
    }
    std::string _fileName = "WSUPLOAD"+this->_getDateTime(true)+"."+this->_getMimeType(this->_request.getHeaders().find("Content-Type")->second, true);
    system(std::string("cp -r "+this->_request.getBodyFile()+" "+this->_trimPath(this->_location.getUploadPath()+"/"+_fileName)).c_str());
    system("echo 'UPLOADED SUCCESFULY' > /tmp/WSRSP00");
    close(_fd);
    return (std::make_pair(this->_generateHeaders("/tmp/WSRSP00")+"\r\n", "/tmp/WSRSP00"));
}

std::string Responder::_indexOfPage(std::string _root, std::string _dir)
{
    DIR *dir;
    struct dirent *dirp;
    struct stat stats;
    struct tm dt;
    std::stringstream _html;
    _html << "<html><head><title>Index of " << _dir << "</title>";
    _html << "<style>body{background-color:#123;color:#FFF;display:flex;justify-content:center;align-items:center;flex-direction:column;min-height:96vh;}";
    _html << "pre {display:flex;justify-content:center;align-items:center;flex-direction:column;width:460px;}";
    _html << "a {text-decoration:none;color:#FFF;overflow:hidden;text-overflow:ellipsis;}";
    _html << ".data span {font-size:12px}";
    _html << ".data {display:flex;justify-content:space-between;font-size:15px;background:#234;padding:.5rem;border-radius:.6rem;min-width:35rem;padding-left:2rem;margin:.2rem;}</style>";
    _html << "</head><body><h1>Index of "+_dir+"</h1><pre>";
    if((dir  = opendir(std::string(_root).c_str())) != NULL)
    {
        while ((dirp = readdir(dir)) != NULL)
        {
            if (dirp->d_name[0] == '.' && dirp->d_name[1] != '.')
                continue;
            if (stat((this->_trimPath(_root+"/"+dirp->d_name)).c_str(), &stats) == 0)
            {
                dt = *(gmtime(&stats.st_ctime));
                if (std::string(dirp->d_name).compare("..") == 0)
                    _html << "<a class='data' href='" << this->_trimPath(std::string(this->_reqPath+"/"+dirp->d_name)) << "'><< Back </a>\n";
                else
                {
                    _html << "<div class='data'><a title='" << dirp->d_name << "' href='" << this->_trimPath(std::string(this->_reqPath+"/"+dirp->d_name)) << "'>" << std::string(dirp->d_name) << "</a><span>";
                    _html << ((dt.tm_mday < 10) ? "0" : "") << dt.tm_mday << "/" << ((dt.tm_mon < 10) ? "0" : "") << dt.tm_mon << "/" << dt.tm_year + 1900 << " ";
                    _html << ((dt.tm_hour < 10) ? "0" : "") << dt.tm_hour << ":" << ((dt.tm_min < 10) ? "0" : "") << dt.tm_min << "</span></div>\n";
                }
            }
        }
        closedir(dir);
    }
    _html << "</pre><br/>webserv/1.0.0</body></html>";
    
    return (this->_creatFile(_html.str(), ".html"));
}

std::string Responder::_creatFile(std::string _body, std::string _ext)
{
    std::string _respath = std::string("/tmp/"+this->_getDateTime(true)+_ext);
    int _fd = open(_respath.c_str(), O_CREAT | O_RDWR , 0400);
    write(_fd, _body.c_str(), _body.length());
    close(_fd);
    return (_respath);
}

std::string Responder::_trimPath(std::string _path)
{
    std::string _newPath;
    for (size_t i = 0; i < _path.length(); i++)
    {
        if (_path[i] == '/' && _path[i] == _path[i + 1])
            continue;
        _newPath += _path[i];
    }
    return (_newPath);
}

size_t  Responder::_cmpath(std::string path, std::string cmval)
{
    size_t res = 0;
    size_t i = 0;
    size_t _ext = path.find_last_of('.');
    path = this->_trimPath(path);
    cmval = this->_trimPath(cmval);
    if (_ext != std::string::npos && cmval.compare(path.substr(_ext)) == 0)
        return (std::string::npos);
    else if (cmval.compare(path) == 0)
        return (std::string::npos - 1);
    else
    {
        path = this->_trimPath(path+'/');
        cmval = this->_trimPath(cmval+'/');
        if (cmval.compare(path) == 0)
            return (std::string::npos - 1);
    }
    while(i < path.length())
    {
        if (path[i] != cmval[i])
            return (res * (cmval[i] == '\0'));
        res += (path[i] == cmval[i] && cmval[i] == '/');
        i++;
    }
    return (res * (cmval[i] == '\0'));
}

bool Responder::_setLocation(std::string _requestPath, std::vector<location_parser> _locations)
{
    size_t  _bestPath = 0;
    this->_reqPath = this->_trimPath(_requestPath);
    for (size_t i = 0; i < _locations.size(); i++)
    {
        size_t _cmp = this->_cmpath(this->_reqPath, this->_trimPath(_locations[i].getLocationPath()));
        this->_location = (_cmp > _bestPath) ?  _locations[i] : this->_location;
        _bestPath = (_cmp > _bestPath) ? _cmp : _bestPath;
    }
    return (!this->_location.getLocationPath().empty());
}

Responder::RESPONSE_DATA Responder::_errorPagesChecker(void)
{
    std::vector<std::string> _errPages = this->_server.getErrorPages();
    if (_errPages.size() > 1)
    {
        for(size_t i = 0; i < _errPages.size() - 1; i++)
        {
            int _v = std::atoi(_errPages[i].c_str());
            if ((_v >= 300 && _v < 600) && (_errPages[i].compare(this->_statusCode) == 0))
            {
                std::string _path = _errPages.back();
                if (!_path.empty() && _path[0] == '/')
                {
                    this->_setLocation(_path, this->_server._locations);
                    this->_setRootPath(_path);
                    this->_prepareResponse();
                    if (this->_statusCode.compare("200") == 0)
                        return (this->_generateResponse());
                    else
                    {
                        _path = this->_generateErrorBody(this->_statusCode);
                        return (std::make_pair(std::string(_generateHeaders(_path)+"\r\n"), _path));
                    }
                }
                else
                    return this->_redirectResponse("301", _path);
            }
        }
    }
    std::string _path = this->_generateErrorBody(this->_statusCode);
    return (std::make_pair(std::string(_generateHeaders(_path)+"\r\n"), _path));
}

std::string Responder::_generateErrorBody(std::string errorCode)
{
    std::string _msg = _getError(errorCode);
    std::string _html = std::string("<html><head><title>"+_msg+"</title><style>body{background-color:#123;color:#FFF;display:flex;justify-content:center;align-items:center;flex-direction:column;height:96vh;}h1{font-size:5rem;margin:.5rem;}</style></head><body><center><h1>"+errorCode+"</h1><h2>"+_msg+"</h2><hr/>webserv/1.0.0</center></body></html>");
    return (this->_creatFile(_html, ".html"));
}

std::string Responder::_getError(std::string errorCode)
{
    std::map<std::string, std::string> statusCodes;

    statusCodes["100"] = "Continue";
    statusCodes["101"] = "Switching protocols";
    statusCodes["102"] = "Processing";
    statusCodes["103"] = "Early Hints";
    statusCodes["200"] = "OK";
    statusCodes["201"] = "Created";
    statusCodes["202"] = "Accepted";
    statusCodes["203"] = "Non-Authoritative Information";
    statusCodes["204"] = "No Content";
    statusCodes["205"] = "Reset Content";
    statusCodes["206"] = "Partial Content";
    statusCodes["207"] = "Multi-Status";
    statusCodes["208"] = "Already Reported";
    statusCodes["226"] = "IM Used";
    statusCodes["300"] = "Multiple Choices";
    statusCodes["301"] = "Moved Permanently";
    statusCodes["302"] = "Found (Previously \"Moved Temporarily\")";
    statusCodes["303"] = "See Other";
    statusCodes["304"] = "Not Modified";
    statusCodes["305"] = "Use Proxy";
    statusCodes["306"] = "Switch Proxy";
    statusCodes["307"] = "Temporary Redirect";
    statusCodes["308"] = "Permanent Redirect";
    statusCodes["400"] = "Bad Request";
    statusCodes["401"] = "Unauthorized";
    statusCodes["402"] = "Payment Required";
    statusCodes["403"] = "Forbidden";
    statusCodes["404"] = "Not Found";
    statusCodes["405"] = "Not Allowed";
    statusCodes["406"] = "Not Acceptable";
    statusCodes["407"] = "Proxy Authentication Required";
    statusCodes["408"] = "Request Timeout";
    statusCodes["409"] = "Conflict";
    statusCodes["410"] = "Gone";
    statusCodes["411"] = "Length Required";
    statusCodes["412"] = "Precondition Failed";
    statusCodes["413"] = "Payload Too Large";
    statusCodes["414"] = "URI Too Long";
    statusCodes["415"] = "Unsupported Media Type";
    statusCodes["416"] = "Range Not Satisfiable";
    statusCodes["417"] = "Expectation Failed";
    statusCodes["418"] = "I'm a Teapot";
    statusCodes["421"] = "Misdirected Request";
    statusCodes["422"] = "Unprocessable Entity";
    statusCodes["423"] = "Locked";
    statusCodes["424"] = "Failed Dependency";
    statusCodes["425"] = "Too Early";
    statusCodes["426"] = "Upgrade Required";
    statusCodes["428"] = "Precondition Required";
    statusCodes["429"] = "Too Many Requests";
    statusCodes["431"] = "Request Header Fields Too Large";
    statusCodes["451"] = "Unavailable For Legal Reasons";
    statusCodes["500"] = "Internal Server Error";
    statusCodes["501"] = "Not Implemented";
    statusCodes["502"] = "Bad Gateway";
    statusCodes["503"] = "Service Unavailable";
    statusCodes["504"] = "Gateway Timeout";
    statusCodes["505"] = "HTTP Version Not Supported";
    statusCodes["506"] = "Variant Also Negotiates";
    statusCodes["507"] = "Insufficient Storage";
    statusCodes["508"] = "Loop Detected";
    statusCodes["510"] = "Not Extended";
    statusCodes["511"] = "Network Authentication Required";

    return (statusCodes[errorCode]);
}

std::string Responder::_getMimeType(std::string _toFind, bool _findExt = false)
{
    std::map<std::string, std::string> mimeTypes;

    mimeTypes["html"] ="text/html";
    mimeTypes["htm"] ="text/html";
    mimeTypes["shtml"] ="text/html";
    mimeTypes["css"] ="text/css";
    mimeTypes["xml"] ="text/xml";
    mimeTypes["gif"] ="image/gif";
    mimeTypes["jpeg"] ="image/jpeg";
    mimeTypes["jpg"] ="image/jpeg";
    mimeTypes["js"] ="application/javascript";
    mimeTypes["atom"] ="application/atom+xml";
    mimeTypes["rss"] ="application/rss+xml";
    mimeTypes["mml"] ="text/mathml";
    mimeTypes["txt"] ="text/plain";
    mimeTypes["jad"] ="text/vnd.sun.j2me.app-descriptor";
    mimeTypes["wml"] ="text/vnd.wap.wml";
    mimeTypes["htc"] ="text/x-component";
    mimeTypes["avif"] ="image/avif";
    mimeTypes["png"] ="image/png";
    mimeTypes["svg"] ="image/svg+xml";
    mimeTypes["svgz"] ="image/svg+xml";
    mimeTypes["tif"] ="image/tiff";
    mimeTypes["tiff"] ="image/tiff";
    mimeTypes["wbmp"] ="image/vnd.wap.wbmp";
    mimeTypes["webp"] ="image/webp";
    mimeTypes["ico"] ="image/x-icon";
    mimeTypes["jng"] ="image/x-jng";
    mimeTypes["bmp"] ="image/x-ms-bmp";
    mimeTypes["woff"] ="font/woff";
    mimeTypes["woff2"] ="font/woff2";
    mimeTypes["jar"] ="application/java-archive";
    mimeTypes["war"] ="application/java-archive";
    mimeTypes["ear"] ="application/java-archive";
    mimeTypes["json"] ="application/json";
    mimeTypes["hqx"] ="application/mac-binhex40";
    mimeTypes["doc"] ="application/msword";
    mimeTypes["pdf"] ="application/pdf";
    mimeTypes["ps"] ="application/postscript";
    mimeTypes["eps"] ="application/postscript";
    mimeTypes["ai"] ="application/postscript";
    mimeTypes["rtf"] ="application/rtf";
    mimeTypes["m3u8"] ="application/vnd.apple.mpegurl";
    mimeTypes["kml"] ="application/vnd.google-earth.kml+xml";
    mimeTypes["kmz"] ="application/vnd.google-earth.kmz";
    mimeTypes["xls"] ="application/vnd.ms-excel";
    mimeTypes["eot"] ="application/vnd.ms-fontobject";
    mimeTypes["ppt"] ="application/vnd.ms-powerpoint";
    mimeTypes["odg"] ="application/vnd.oasis.opendocument.graphics";
    mimeTypes["odp"] ="application/vnd.oasis.opendocument.presentation";
    mimeTypes["ods"] ="application/vnd.oasis.opendocument.spreadsheet";
    mimeTypes["odt"] ="application/vnd.oasis.opendocument.text";
    mimeTypes["pptx"] ="application/vnd.openxmlformats-officedocument.presentationml.presentation";
    mimeTypes["xlsx"] ="application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    mimeTypes["docx"] ="application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    mimeTypes["wmlc"] ="application/vnd.wap.wmlc";
    mimeTypes["wasm"] ="application/wasm";
    mimeTypes["7z"] ="application/x-7z-compressed";
    mimeTypes["cco"] ="application/x-cocoa";
    mimeTypes["jardiff"] ="application/x-java-archive-diff";
    mimeTypes["jnlp"] ="application/x-java-jnlp-file";
    mimeTypes["run"] ="application/x-makeself";
    mimeTypes["pl"] ="application/x-perl";
    mimeTypes["pm"] ="application/x-perl";
    mimeTypes["prc"] ="application/x-pilot";
    mimeTypes["pdb"] ="application/x-pilot";
    mimeTypes["rar"] ="application/x-rar-compressed";
    mimeTypes["rpm"] ="application/x-redhat-package-manager";
    mimeTypes["sea"] ="application/x-sea";
    mimeTypes["swf"] ="application/x-shockwave-flash";
    mimeTypes["sit"] ="application/x-stuffit";
    mimeTypes["tcl"] ="application/x-tcl";
    mimeTypes["tk"] ="application/x-tcl";
    mimeTypes["der"] ="application/x-x509-ca-cert";
    mimeTypes["pem"] ="application/x-x509-ca-cert";
    mimeTypes["crt"] ="application/x-x509-ca-cert";
    mimeTypes["xpi"] ="application/x-xpinstall";
    mimeTypes["xhtml"] ="application/xhtml+xml";
    mimeTypes["xspf"] ="application/xspf+xml";
    mimeTypes["zip"] ="application/zip";
    mimeTypes["bin"] ="application/octet-stream";
    mimeTypes["exe"] ="application/octet-stream";
    mimeTypes["dll"] ="application/octet-stream";
    mimeTypes["deb"] ="application/octet-stream";
    mimeTypes["dmg"] ="application/octet-stream";
    mimeTypes["iso"] ="application/octet-stream";
    mimeTypes["img"] ="application/octet-stream";
    mimeTypes["msi"] ="application/octet-stream";
    mimeTypes["msp"] ="application/octet-stream";
    mimeTypes["msm"] ="application/octet-stream";
    mimeTypes["mid"] ="audio/midi";
    mimeTypes["midi"] ="audio/midi";
    mimeTypes["kar"] ="audio/midi";
    mimeTypes["mp3"] ="audio/mpeg";
    mimeTypes["ogg"] ="audio/ogg";
    mimeTypes["m4a"] ="audio/x-m4a";
    mimeTypes["ra"] ="audio/x-realaudio";
    mimeTypes["3gpp"] ="video/3gpp";
    mimeTypes["3gp"] ="video/3gpp";
    mimeTypes["ts"] ="video/mp2t";
    mimeTypes["mp4"] ="video/mp4";
    mimeTypes["mpeg"] ="video/mpeg";
    mimeTypes["mpg"] ="video/mpeg";
    mimeTypes["mov"] ="video/quicktime";
    mimeTypes["webm"] ="video/webm";
    mimeTypes["flv"] ="video/x-flv";
    mimeTypes["m4v"] ="video/x-m4v";
    mimeTypes["mng"] ="video/x-mng";
    mimeTypes["asx"] ="video/x-ms-asf";
    mimeTypes["asf"] ="video/x-ms-asf";
    mimeTypes["wmv"] ="video/x-ms-wmv";
    mimeTypes["avi"] ="video/x-msvideo";

    if (_findExt)
    {
        std::map<std::string, std::string>::iterator it = mimeTypes.begin();
        for (; it != mimeTypes.end(); ++it)
            if (it->second.compare(_toFind) == 0)
                return it->first;
        return ("");
    }
    size_t ppos =  _toFind.find_last_of(".");
    if (ppos == std::string::npos)
        return (mimeTypes["txt"]);
    std::map<std::string, std::string>::iterator it = mimeTypes.find(_toFind.substr(++ppos));
    if (it == mimeTypes.end())
        return (mimeTypes["txt"]);
    return (it->second);
}

Responder::~Responder()
{
    system("rm -rf /tmp/WSRSP*");
}
