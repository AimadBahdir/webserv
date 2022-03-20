/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sock_server.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:34:52 by wben-sai          #+#    #+#             */
/*   Updated: 2022/03/20 10:29:28 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctime>
#include <map>
#include <unistd.h>
#include<fcntl.h> 
#include <vector>
#include "../parser/parser.hpp"
#include "../parser/request_parser.hpp"
#include "../responder/responder.hpp"

// class server - request - response
class SRR 
{
    private:
        std::string _type_sock;
        server_parser _server;
        request_parser *_request;
        Responder *_response;
    public:
        size_t file_response;
        size_t Length_read;
        int     _number_request;
        size_t FileLength;
        SRR();
        ~SRR();
        SRR(std::string _type_sock, server_parser _server, std::string _filename);
        std::string get_type_sock();
        server_parser get_server();
        request_parser *get_request_parser();
        Responder *get_responser();
        void set_responser(Responder * response);
        void set_request_parser(request_parser *_request);
        size_t _getFileLength(std::string _fpath);
        
};

class sock_server
{
    private:
        fd_set FDs_readability, FDs_writability;
        fd_set FDs_readability_copy, FDs_writability_copy;
        
        std::map<int, SRR *> M_FSRR; 
        
        int  _create_socket(server_parser srv);
        void _bind(int fd_sock ,size_t port, std::string host);
        void _listen(int fd_sock);
        int  _select();
        void _accept(int fd_sock, server_parser srv);
        bool _recv(int connectionServerSockFD);
        void _send(int connectionServerSockFD, server_parser srv, std::vector<server_parser> servers);
        void ManagementFDs(std::vector<server_parser> servers);
       
    public:
        sock_server(std::vector<server_parser> servers);
        ~sock_server();
        
};

#endif /* SERVER */
