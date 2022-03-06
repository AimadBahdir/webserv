
#pragma once
#include "../configStructs.cpp"
#include "../../parser/server_parser.hpp"
#include "../../parser/location_parser.hpp"
#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <sstream>

class Responder
{
    public:
        explicit Responder(request_parser);
        explicit Responder(Responder const & r);
        Responder& operator=(Responder const & r);
        ~Responder (void);
        std::string response(void);
        std::string _generateErrorBody(std::string errorMessage);
        std::string _indexOfPage(std::string _root, std::string _dir);

    private:
        request_parser     _request;
        location_parser    _location;
        std::string        _statusCode;

        bool            _setLocation(std::string _reqPath, std::vector<location_parser> _locations);
        bool            _errorsChecker(void);
        std::string     _cgiResponse(void);
        std::string     _getMethode(void);
        std::string     _postMethode(void);
        std::string     _deleteMethode(void);
        std::string     _uploadFile(void);
        std::string     _getErrorPage(void);
        std::string     _getMimeType(std::string path);
        std::string     _getError(std::string errorCode);
        size_t          _cmpath(std::string path, std::string cmval);
        // std::string _generateResponse();
};
