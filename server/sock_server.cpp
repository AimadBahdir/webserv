/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sock_server.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 10:34:36 by wben-sai          #+#    #+#             */
/*   Updated: 2022/03/15 16:46:14 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sock_server.hpp"

sock_server::sock_server(std::vector<server_parser> servers)
{
    int fd_sock;
    if(servers.size() == 0)
        exit(2);
    for (std::vector<server_parser>::iterator it = servers.begin(); it != servers.end(); it++)
    {
        fd_sock = _create_socket(*it);
        _bind(fd_sock, it->getPort(), it->getHost());
        _listen(fd_sock);
    }
    ManagementFDs();
}

int sock_server::_create_socket(server_parser srv)
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
        M_FSRR.insert(std::make_pair(fd_sock, new SRR("server_socket", srv, "")));
        std::cout << "socket ID = " << fd_sock << std::endl;
    }
    return (fd_sock);
}

void sock_server::_bind(int fd_sock ,size_t port, std::string host)
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
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(host.c_str());

    if (bind(fd_sock, (sockaddr*)&addr, sizeof(addr)) == 0)
        std::cout << "server is binded to port "<< port << std::endl;
    else
    {
        std::cout << "binding failed" <<  std::endl;
        exit(1);
    }
}

void sock_server::_listen(int fd_sock)
{
    /* ----------------------------------------------------------------------------------------
    int listen(int sockfd, int backlog);
        sockfd : the socket descriptor
        backlog : length to which the queue of pending connections for sockfd
        -- Note : listen() is non-blocking : return immediately.
    ---------------------------------------------------------------------------------------- */
    
    if (listen(fd_sock, 1) == 0)
        std::cout << "listenning ..." << std::endl;
    else
    {
        std::cout << "listen failed" <<  std::endl;
        exit(1);
    }
}

void sock_server::_accept(int fd_sock, server_parser srv)
{
    /* ----------------------------------------------------------------------------------------
    int accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);
        sockfd : the socket descriptor
        addr : where the address of the connecting socket shall be return
        addrlen : sizeof (addr)
        -- Note : accept() is blocking : wait for connection before returning
        -- Note : listen() is used by the server only as a way to get new sockets.
    ---------------------------------------------------------------------------------------- */
    
    int connectionServerSockFD = accept(fd_sock, NULL, 0);
    //fcntl(new_fd, F_SETFL, O_NONBLOCK); /* Change the socket into non-blocking state	*/
    if(connectionServerSockFD == -1) 
    {
        std::cout << "Failed to accept connection request" << std::endl;
        exit(1);
    }
    else
    {
        std::cout << "Client with Id " << connectionServerSockFD << " is connect" << std::endl; 
        FD_SET(connectionServerSockFD, &FDs_readability);
        std::string file_name = std::to_string(std::time(nullptr)) + "_" + std::to_string(connectionServerSockFD);
        M_FSRR.insert(std::make_pair(connectionServerSockFD, new SRR("connection_socket",srv, file_name)));
    }
}

void sock_server::_recv(int connectionServerSockFD)
{
    char buf[10240];
    ssize_t lenString = recv(connectionServerSockFD, buf, (sizeof(buf)), 0);
    buf[lenString] = '\0';
    if(lenString == 0)
    {
        FD_CLR(connectionServerSockFD, &FDs_readability);
        close(connectionServerSockFD);
        std::cout << "Client with Id " << connectionServerSockFD << " is disconnect" << std::endl;
    }
    else
    {
        request_parser *temp = M_FSRR.find(connectionServerSockFD)->second->get_request_parser();
        try
        {
            temp->sendLine(buf);
            if (temp->getStatus())
            {
                FD_SET(connectionServerSockFD, &FDs_writability);
                FD_CLR(connectionServerSockFD, &FDs_readability);
            }
            std::cout << "tmp"<< temp->getPath() << std::endl;
        }
        catch(const char *str) {
            //std::cout << str << std::endl;
        }
    }
}

void sock_server::_send(int connectionServerSockFD, server_parser srv)
{
    (void)srv;

    SRR *srr = (M_FSRR.find(connectionServerSockFD))->second; 
    std::pair<std::string, std::string> paiir("HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 68\nConnection: keep-alive\nCache-Control: max-age=0\nUpgrade-Insecure-Requests: 1\nCookie: PHPSESSID=298zf09hf012fh2; csrftoken=u32t4o3tb3gg43; _gat=1\nUser-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_14_6) AppleWebKit/537.36 (KHTML] = like Gecko) Chrome/89.0.4389.114 Safari/537.36\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9\nSec-Fetch-Site: cross-site\nSec-Fetch-Mode: navigate\nSec-Fetch-User: ?1\nSec-Fetch-Dest: document\nAccept-Encoding: gzip, deflate, br\nAccept-Language: en-US,en;q=0.9\n", "/Users/wben-sai/Desktop/webser3/server/response");
    
    
    std::string res;
    if(srr->FileLength == 0)
    {   
        srr->FileLength = srr->_getFileLength(paiir.second);
        srr->file_response = open(paiir.second.c_str(), O_RDONLY);
        res = paiir.first;
    }
        
    char buf[10241];
    int len_read = read(srr->file_response, buf, (sizeof(char) * 10240));
    if(len_read != -1)
    {
        buf[len_read] = '\0';
        srr->Length_read += len_read;
    }
    
    res += buf;
    
    std::cout <<"res = "<< res << std::endl;
    
    send(connectionServerSockFD, res.c_str() , res.length(), 0);

    if(srr->Length_read == srr->FileLength)
    {
        srr->Length_read = 0;
        srr->FileLength = 0;
        close(srr->file_response);
        FD_SET(connectionServerSockFD, &FDs_readability);
        FD_CLR(connectionServerSockFD, &FDs_writability);
        std::map<std::string, std::string>::iterator it = (srr->get_request_parser()->getHeaders()).find("Connection");
        if(it != (srr->get_request_parser()->getHeaders()).end() && it->second == "Close")
        {
            FD_CLR(connectionServerSockFD, &FDs_readability);
            close(connectionServerSockFD);
        }
        srr->_number_request++;
        std::string file_name = std::to_string(std::time(nullptr)) + "_" + std::to_string(connectionServerSockFD)+ "_" + std::to_string(srr->_number_request);
        delete srr->get_request_parser();
        srr->get_request_parser()->removeFile();
        srr->set_request_parser(new request_parser("/tmp/" + file_name));
    }
}

int sock_server::_select()
{
    int res = select(M_FSRR.rbegin()->first + 1, &FDs_readability_copy, &FDs_writability_copy, NULL, 0);
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
            for (std::map<int, SRR *>::iterator it = M_FSRR.begin(); it != M_FSRR.end(); it++)
            {
                if (FD_ISSET(it->first , &FDs_writability_copy))
                {
                    _send(it->first, (it->second)->get_server());
                }
                else if (FD_ISSET(it->first , &FDs_readability_copy)) 
                {
                    if((it->second)->get_type_sock() == "server_socket")
                        _accept(it->first, ((it->second)->get_server()));
                    else 
                       _recv(it->first);
                }
            }
        }
    }
}   
   