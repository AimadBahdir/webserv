
#pragma once
#include "../configStructs.cpp"
#include "./response.cpp"

namespace RSP {
    class Responder
    {
        typedef std::map<std::string, std::string>  request_map;
        public:
            explicit Responder(server);
            explicit Responder(Responder const & r);
            Responder& operator=(Responder const & r);
            ~Responder (void);
            RSP::Response Respond(request_map);
        private:
            server _server;
            std::string CGI_Response();
            std::string GET_Methode();
            std::string POST_Methode();
            std::string DELTE_Methode();
            std::string UploadFile();
            std::string GetErrorPage();
            std::string GetMimeType(std::string path);
            std::string GenerateErrorPage(std::string errorMessage);
            std::string GetError(std::string errorCode);
    };
}
