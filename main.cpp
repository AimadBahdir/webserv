/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abahdir <abahdir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 11:13:52 by wben-sai          #+#    #+#             */
/*   Updated: 2022/03/17 14:05:25 by abahdir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./server/sock_server.hpp"

int     main(int ac , char *av[])
{

    parser *conf;

    if (ac == 2)
    {
        try
        {
            conf = new parser(av[1]);
            sock_server *ser = new sock_server(conf->_servers);
            (void) ser;
        }
        catch(const char *str)
        {
            std::cerr << str << std::endl;
            exit(1);
        }
    }
    else
    {
        std::cerr << "Please provide a config file" << std::endl;
        return 1;
    }
    return (0);
}