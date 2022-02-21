/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sock_server.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:34:52 by wben-sai          #+#    #+#             */
/*   Updated: 2022/02/21 16:26:03 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <map>
#include <vector>

//----------------------------------------------------------------

struct location
{
    std::vector<std::string> accepted_requests;
    std::string location_path;
    std::string root_path;
    std::vector<std::string> index;
    std::string upload_path;
    std::string cgi_path;
    std::pair<int, std::string> redirection;
    bool auto_index;
};

struct server
{
    std::string host;
    size_t port;
    std::vector<std::string> names;
    std::vector<std::string> error_pages;
    std::vector<location> locations;
    int clientMaxBodySize;
};

//----------------------------------------------------------------

// class server - request - response
class SRR 
{
    private:
        std::string _type_sock;
        server _server;
        std::string _request;
        std::string _response;
    public:
        SRR(){};
        SRR(std::string _type_sock, server _server)
        {
            this->_type_sock = _type_sock;
            this->_server = _server;
        };
        std::string get_type_sock(){return _type_sock;}
        server get_server(){return _server;}
        //std::string get_request(){return _request;}
        //std::string get_response(){return server;}
};

class sock_server
{
    private:
        fd_set FDs_readability, FDs_writability;
        fd_set FDs_readability_copy, FDs_writability_copy;
        
        std::map<int, SRR> M_FSRR; 
        
        int  _create_socket(server srv);
        void _bind(int fd_sock ,size_t port, std::string host);
        void _listen(int fd_sock);
        int  _select();
        void _accept(int fd_sock, server srv);
        void _recv(int connectionServerSockFD);
        void ManagementFDs();
    public:
        sock_server(std::vector<server> servers);
        ~sock_server();
        
};

#endif /* SERVER */
