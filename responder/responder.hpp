
#pragma once
#include "../configStructs.cpp"
#include "../../parser/server_parser.hpp"
#include "../../parser/request_parser.hpp"
#include "../../parser/location_parser.hpp"
#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <sstream>
#include <fstream>

class Responder
{
    public:
        typedef std::pair<std::string, std::string> RESPONSE_DATA;
        explicit Responder(request_parser, server_parser);
        explicit Responder(Responder const & r);
        Responder& operator=(Responder const & r);
        ~Responder (void);
        RESPONSE_DATA   response(void);
    private:
        request_parser     _request;
        server_parser      _server;
        location_parser    _location;
        std::string        _reqPath;
        std::string        _statusCode;
        std::string        _rootPath;
        std::string        _indexPath;
        bool               _REDIRECT;
        bool               _UPLOAD;
        bool               _CGI;

        void            _prepareResponse(void);
        void            _setRootPath(void);
        bool            _setIndexs(void);
        void            _setCGIResponseFile(std::string _path);
        char**          _EnvarCGI();
        bool            _setIndex(std::string _index);
        bool            _setLocation(std::string _reqPath, std::vector<location_parser> _locations);
        bool            _errorsChecker(void);
        RESPONSE_DATA   _errorPagesChecker(void);
        RESPONSE_DATA   _staticResponse(void);
        RESPONSE_DATA   _redirectResponse();
        RESPONSE_DATA   _cgiResponse(void);
        RESPONSE_DATA   _uploadFile(void);
        RESPONSE_DATA    _generateResponse();
        std::string     _generateHeaders(std::string _responseFILE);
        std::string     _toUpper(const char* _str);
        std::string     _getDateTime(bool _fileName);
        std::string     _trimPath(std::string _path);
        std::string     _postMethode(void);
        std::string     _deleteMethode(void);
        std::string     _getErrorPage(void);
        std::string     _getMimeType(std::string path);
        std::string     _getError(std::string errorCode);
        std::string     _generateErrorBody(std::string errorMessage);
        std::string     _indexOfPage(std::string _root, std::string _dir);
        size_t          _cmpath(std::string path, std::string cmval);
        size_t          _getFileLength(std::string _fpath);
};
