#pragma once

#include "utils.hpp"
#include "location_parser.hpp"

class location_parser;

struct id {
	int	port;
	int size;
	int	host;
	int root;
	int names;
	int	error;
};

class server_parser
{
	private :
		int								port;
		int								clientMaxBodySize;
		std::string						host;
		std::string						root_path;
		std::vector<std::string>		names;
		std::vector<std::string>		error_pages;

		std::vector<std::string>		_serverBlock;
	    
		struct id						id;

	public :

		// constructors and overloads :
		server_parser();
		server_parser(std::vector<std::string> block);
		~server_parser();

		server_parser &operator=(server_parser const &src);


		//	Setters :

		bool						setPort(std::vector<std::string> tokens);
		bool						setHost(std::vector<std::string> tokens);
		bool						setRoot(std::vector<std::string> tokens);
		bool						setNames(std::vector<std::string> tokens);
		bool						setErrorPages(std::vector<std::string> tokens);
		bool						setMaxSize(std::vector<std::string> tokens);

		bool						set_directives(std::vector<std::string> tokens);
		void						setDefault();


		//	Getters :
	   	
		std::vector<location_parser>	_locations;
		std::vector<std::string>		_locationBlock;

		int							getPort();
		int							getMaxSzie();
		std::string					getHost();
		std::string					getRoot();
		std::vector<std::string>    getNames();
		std::vector<std::string>    getErrorPages();
		std::vector<std::string>    getServerBlock();

};