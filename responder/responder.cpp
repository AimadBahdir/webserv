#include "./responder.hpp"

Responder::Responder(servers_vec servers) : _servers(servers)
{
}

Responder::Responder(Responder const & r)
{
    (*this) = r;
}

Responder& Responder::operator=(Responder const & r)
{
    this->_servers = r._servers;
    return (*this);
}

Responder::~Responder()
{
}

std::string Responder::Response(request_map request)
{
    
    return (request["URI"]);
}


