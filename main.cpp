#include "parser.hpp"
#include "server_parser.hpp"
#include "utils.hpp"


int     main(int ac , char *av[])
{

    parser *conf;

    if (ac == 2)
    {
        try
        {
            conf = new parser(av[1]);
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

    std::cout << conf->_servers.size() << std::endl;

    // std::cout << conf->_servers[0]._locations[2].getRootPath() << std::endl;

    std::cout << conf->_servers[0]._locations[0].getRedirection().second <<std::endl;
    delete conf;
    return 0;
}


