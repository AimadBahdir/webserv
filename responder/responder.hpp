
#pragma once
#include "../configStructs.cpp"
#include <algorithm>

class Responder
{
    public:
        explicit Responder(request);
        explicit Responder(Responder const & r);
        Responder& operator=(Responder const & r);
        ~Responder (void);
    private:
        request _req;
        std::string CGI_Response();
        std::string GET_Methode();
        std::string POST_Methode();
        std::string DELTE_Methode();
        std::string UploadFile();
        std::string GetErrorPage();
        std::string GetMimeType(std::string path);
        std::string GenerateErrorPage(std::string errorMessage);
        std::string GetError(std::string errorCode);
        size_t      _cmpath(std::string path, std::string cmval);
        location    _getLocation(std::string _reqPath, std::vector<location> _locations);
};
