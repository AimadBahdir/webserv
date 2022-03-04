
#pragma once
#include "../configStructs.cpp"
#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

class Responder
{
    public:
        explicit Responder(request);
        explicit Responder(Responder const & r);
        Responder& operator=(Responder const & r);
        ~Responder (void);
        std::string response(void);
        std::string _generateErrorBody(std::string errorMessage);
        std::string _indexOfPage(std::string _root, std::string _dir);

    private:
        request _request;
        location _location;

        std::string _cgiResponse();
        std::string _getMethode();
        std::string _postMethode();
        std::string _deleteMethode();
        std::string _uploadFile();
        std::string _getErrorPage();
        std::string _getMimeType(std::string path);
        std::string _getError(std::string errorCode);
        size_t      _cmpath(std::string path, std::string cmval);
        location    _getLocation(std::string _reqPath, std::vector<location> _locations);
        // std::string _generateResponse();
};
