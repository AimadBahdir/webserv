
#pragma once
#include "../configStructs.cpp"

class Responder
{
    typedef std::vector<server>                 servers_vec;
    typedef std::map<std::string, std::string>  request_map;

    public:
        explicit Responder(servers_vec);
        explicit Responder(Responder const & r);
        Responder& operator=(Responder const & r);
        ~Responder (void);
        std::string Response(request_map);
    private:
        servers_vec _servers;
        // std::string CGI_Response();
        // std::string GET_Methode();
        // std::string POST_Methode();
        // std::string DELTE_Methode();
        // std::string UploadFile();
        // std::string GetErrorPage();
};