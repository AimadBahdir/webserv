#pragma once

#include "utils.hpp"
#include "server_parser.hpp"

class server_parser;

class parser {

	private :
		
		std::vector<std::string>		_block;
		std::string						_line;

	public :

		parser(std::string av);
		parser();
		~parser();
		
		parser &operator=(parser const &src);
	
			
		std::vector<server_parser>	_servers;
		
		void	display();
};