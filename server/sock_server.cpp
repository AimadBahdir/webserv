/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sock_server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:34:36 by wben-sai          #+#    #+#             */
/*   Updated: 2022/02/21 09:52:27 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sock_server.hpp"

sock_server::sock_server(std::vector<server> servers)
{
   
    for (std::vector<server>::iterator it = servers.begin(); it != servers.end(); it++)
    {
        _create_socket();
        _bind(it->port, it->host);
        _listen();
    }
    ManagementFDs();
}

void sock_server::_create_socket()
{
    /* ----------------------------------------------------------------------------------------
    int sockId = socket(domain, type, protocol) 
        domain (family)
            AF_INET : (adress family internet Ipv4)
            PF_INET : (protocol family internet Ipv4)
            ...
        type 
            SOCK_STREAM : TCP
            SOCK_DGRAM : UDP
            ...
        protocol
            IP      0       # internet protocol
            TCP     6       # transmission control protocol
            UDP     17      # user datagram protocol 
            ...
    ---------------------------------------------------------------------------------------- */
    int fd_sock;
    if ((fd_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        std::cout << "Failed to create a socket" << std::endl;
        exit(1);
    }
    else
    {
        FD_SET(fd_sock, &FDs_readability);

        list_socket_server.push_back(fd_sock);

        std::pair<int, std::string> first(fd_sock, "server " + fd_sock);
        std::pair<std::string, std::string> second("request", "response");
        FSRR.insert(std::make_pair(first, second));

        std::cout << "socket ID = " << fd_sock << std::endl;
    }
}

void sock_server::_bind(size_t port, std::string host)
{
    /* ----------------------------------------------------------------------------------------
    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
        sockfd : the socket descriptor
        addr : we determine the adress based on the used family.
           |  AF_UNIX Family  |                                    AF_INET Family                                             |                             |
           |       ...        |   struct sockAddress;                                                                         |
           |       ...        |   memset(&sockAddress, 0, sizeog(sockAdress));                                                |
           |       ...        |   sockAddress.sinfamily = AF_INET;                        // define the used domain           |    
           |       ...        |   sockAddress.sin_port = htons(5000);                     // sudo setstat -ntlp               |    
           |       ...        |   sockAddress.sin_addr.s_addr = htonl(INADDR_ANY);        // Prmit any incoming IP adrress    |        
           |       ...        |              "                = inet_addr("127.0.0.1");   // Prmit any client request         |    
        addrlen : sizeof(sockAddress);
    ---------------------------------------------------------------------------------------- */
    struct sockaddr_in srv;
    srv.sin_family = AF_INET;
    srv.sin_port = htons(port);
    srv.sin_addr.s_addr = inet_addr(host.c_str());

    if (bind(*(list_socket_server.rbegin()), (sockaddr*)&srv, sizeof(srv)) == 0)
        std::cout << "server is binded to port "<< port << std::endl;
    else
    {
        std::cout << "binding failed" <<  std::endl;
        exit(1);
    }
}

void sock_server::_listen()
{
    /* ----------------------------------------------------------------------------------------
    int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);
        sockfd : the socket descriptor
        addr : where the address of the connecting socket shall be return
        addrlen : sizeof (addr)
        -- Note : accept() is blocking : wait for connection before returning
        -- Note : listen() is used by the server only as a way to get new sockets.
    ---------------------------------------------------------------------------------------- */
    
    if (listen(*(list_socket_server.rbegin()), 1) == 0)
        std::cout << "listenning ..." << std::endl;
    else
    {
        std::cout << "listen failed" <<  std::endl;
        exit(1);
    }
}

void sock_server::_accept()
{
    // 6 - accept the connection request
    int connectionServerSockFD = accept(sock, NULL, 0);
    //fcntl(new_fd, F_SETFL, O_NONBLOCK); /* Change the socket into non-blocking state	*/
    FD_SET(connectionServerSockFD, &FDs_readability);
    FD_MAP.insert(std::pair<int, std::string>(connectionServerSockFD, ""));
    if(connectionServerSockFD == -1) 
    {
        std::cout << "Failed to accept connection request" << std::endl;
        exit(1);
    }
    std::cout << "Client with Id " << connectionServerSockFD << " is connect" << std::endl; 
}

void sock_server::_recv(int FDs)
{
   char buf[1024];
    ssize_t lenString = recv(FDs, buf, (sizeof(buf)), 0);
    buf[lenString] = '\0';
    if(lenString == 0)
    {
        FD_CLR(FDs, &FDs_readability);
        close(FDs);
        std::cout << "Client with Id " << FDs << " is disconnect" << std::endl;
    }
    else
    {
        std::string res = buf;
        FD_MAP[FDs] = FD_MAP[FDs] + " " + buf;
        send(FDs, "alothhhna", 9, 0);
        for (std::map<int , std::string>::iterator i = FD_MAP.begin(); i != FD_MAP.end(); i++)
            std::cout << "fd = " << i->first << " val = "<< i->second << std::endl;   
    }
}

int sock_server::_select()
{
    int res = select((FSRR.rbegin()->first).first + 1, &FDs_readability_copy, NULL, NULL, 0);
    if (res == -1)
    {
        std::cout << "Select failed" <<  std::endl;
        exit(1);
    }
    return (res);
}


void sock_server::ManagementFDs()
{
    while (true)
    {
        FDs_readability_copy = FDs_readability;
        FDs_writability_copy = FDs_writability;
        
        if (_select() != 0)
        {
            for (std::map<std::pair<int, std::string>, std::pair<std::string, std::string> >::iterator it = FSRR.begin(); it != FSRR.end(); it++)
            {
                if (FD_ISSET((it->first).first , &FDs_readability_copy))
                {
                    
                    if((it->first).first == sock)
                        _accept();
                    else 
                       _recv((it->first).first);
                }   
            }
        }
    }
    close(sock);
}   
   