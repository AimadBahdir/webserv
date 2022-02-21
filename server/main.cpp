/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 11:13:52 by wben-sai          #+#    #+#             */
/*   Updated: 2022/02/21 11:32:57 by wben-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sock_server.cpp"


int main()
{


    //----------------------------------------------------------------
    
    std::vector<server> servers;

    server srv1;
    srv1.host = "127.0.0.1";
    srv1.port = 8000;
    srv1.names.push_back("server1");
    srv1.names.push_back("server2");
    srv1.names.push_back("server3");
    srv1.error_pages.push_back("500");
    srv1.error_pages.push_back("501");
    srv1.error_pages.push_back("502");
    srv1.error_pages.push_back("./50x.html");

    location loc1;
    loc1.location_path = "/home";
    loc1.auto_index = false;
    loc1.cgi_path = "/Users/etc/cgi";
    loc1.index.push_back("index.html");
    loc1.index.push_back("index.htm");
    loc1.root_path = "/Users/home/";

    location loc2;
    loc2.location_path = "/about";
    loc2.auto_index = true;
    loc2.cgi_path = "/Users/etc/cgi";
    loc2.index.push_back("index.html");
    loc2.index.push_back("index.htm");
    loc2.root_path = "/Users/about/";

    srv1.locations.push_back(loc1);
    srv1.locations.push_back(loc2);
    
    servers.push_back(srv1);
    servers.push_back(srv1);
    servers[1].port = 3000;

    //----------------------------------------------------------------
 
    sock_server *ser = new sock_server(servers);
    (void) ser;
    return (0);
}