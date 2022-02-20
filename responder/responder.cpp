#include "./responder.hpp"

Responder::Responder(server srv) : _server(srv) {}

Responder::Responder(Responder const & r)
{
    (*this) = r;
}

Responder& Responder::operator=(Responder const & r)
{
    this->_server = r._server;
    return (*this);
}

Responder::~Responder() {}

std::string Responder::Response(request_map request)
{
    // if (request["Methode"] == "GET")
        
    return (request["URI"]);
}

std::string Responder::CGI_Response() 
{
    return ("Res");
}

std::string Responder::GET_Methode() 
{
    return ("Res");
}

std::string Responder::POST_Methode() 
{
    return ("Res");
}

std::string Responder::DELTE_Methode() 
{
    return ("Res");
}

std::string Responder::UploadFile() 
{
    return ("Res");
}

std::string Responder::GetErrorPage() 
{
    return ("Res");
}
