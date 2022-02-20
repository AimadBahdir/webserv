/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:34:52 by wben-sai          #+#    #+#             */
/*   Updated: 2022/02/19 15:04:38 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <map>

class server
{
    private:
        int sock;
        int PORT;
        struct sockaddr_in srv;
        fd_set FDs_readability, FDs_writability;
        fd_set FDs_readability_copy, FDs_writability_copy;
        std::map<int , std::string> FD_MAP;

        void _create_socket();
        void _bind();
        void _listen();
        int  _select();
        void _accept();
        void _recv(int FDs);
        void ManagementFDs();
    public:
        server(int Pport ,const char *host);
        ~server();
        
};

#endif /* SERVER */
