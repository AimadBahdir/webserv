/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sock_server.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:34:52 by wben-sai          #+#    #+#             */
/*   Updated: 2022/03/14 16:29:13 by wben-sai         ###   ########.fr       */
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

// class server - request - response
class SRR 
{
    private:
        std::string _type_sock;
        server_parser _server;
        request_parser *_request;
        std::string _response;
    public:
        size_t file_response;
        size_t Length_read;
        int     _number_request;
        size_t FileLength;
        SRR(){};
        SRR(std::string _type_sock, server_parser _server, std::string _filename)
        {
            Length_read = 0;
            this->_type_sock = _type_sock;
            this->_server = _server;
            this->_number_request = 0;
            this->FileLength = 0;
            if(!_filename.empty())
                _request = new request_parser("/tmp/" + _filename);
            
        }
        std::string get_type_sock(){return _type_sock;}
        server_parser get_server(){return _server;}
        request_parser *get_request_parser(){return _request;}
        void set_request_parser(request_parser *_request){this->_request = _request;}
        size_t _getFileLength(std::string _fpath)
        {
            std::ifstream _file;
            size_t length;

            _file.open (_fpath.c_str(), std::ios::binary);
            _file.seekg (0, std::ios::end);
            length = _file.tellg();
            _file.close();
            return (length);
        }
        //std::string get_response(){return server;}
        
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
        void _recv(int connectionServerSockFD);
        void _send(int connectionServerSockFD, server_parser srv);
        void ManagementFDs();
       
    public:
        sock_server(std::vector<server_parser> servers);
        ~sock_server();
        
};

#endif /* SERVER */
