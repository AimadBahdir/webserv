#include "server_parser.hpp"


server_parser::server_parser(){
	setDefault();
}
server_parser::~server_parser(){}

 server_parser &server_parser::operator=(server_parser const &src)
 {
	if (this == &src)
		return *this;
	root_path = src.root_path;
	host = src.host;
	port = src.port;
	names = src.names;
	error_pages = src.error_pages;
	clientMaxBodySize = src.clientMaxBodySize;
	_serverBlock = src._serverBlock;
	_locations = src._locations;
	_locationBlock = src._locationBlock;
	
	return *this;	
 }

void		server_parser::setDefault()
{
	port = 80;
	host = "0.0.0.0";
	clientMaxBodySize = 0;

	id.port = 0;
	id.size = 0;
	id.host = 0;
	id.root = 0;
	id.names = 0;
	id.error = 0;

}

bool						server_parser::setPort(std::vector<std::string> tokens)
{
	if(tokens.size() != 2)
		return false;
	if(!is_digit(tokens[1]) || tokens[1].length() > 6)
		return false;
	int tmp = atoi(tokens[1].c_str());
	if (tmp < 0 || tmp > 65535)
		return false;
	port = tmp;
	id.port++;
	if (id.port > 1)
		return false;
	return true;
}


bool						server_parser::setHost(std::vector<std::string> tokens)
{
	if(tokens.size() != 2)
		return false;
	host = tokens[1];
	id.host++;
	if (id.host > 1)
		return false;
	return true;
}

bool						server_parser::setNames(std::vector<std::string> tokens)
{
	if (tokens.size() < 2)
		return false;
	
	std::vector<std::string>::iterator it = tokens.begin() + 1;

	for(; it != tokens.end() ; it++)
		names.push_back(*it);
	id.names++;
	if (id.names > 1)
		return false;	
	return true;
}

bool						server_parser::setRoot(std::vector<std::string> tokens)
{
	if(tokens.size() != 2)
		return false;
	root_path = tokens[1];
	id.root++;
	if (id.root > 1)
		return false;
	return true;
}

bool						server_parser::setErrorPages(std::vector<std::string> tokens)
{
	if (tokens.size() < 2)
		return false;
	
	std::vector<std::string>::iterator it = tokens.begin() + 1;

	for(; it != tokens.end() ; it++)
		error_pages.push_back(*it);
	id.error++;
	if (id.error > 1)
		return false;
	return true;
}


bool						server_parser::setMaxSize(std::vector<std::string> tokens)
{
	if(tokens.size() != 2)
		return false;
	if(!is_digit(tokens[1]) || tokens[1].length() > 4)
		return false;
	int tmp = atoi(tokens[1].c_str());
	if (tmp < 0 || tmp > 1024)
		return false;
	clientMaxBodySize = tmp;
	id.size++;
	if (id.size > 1)
		return false;
	return true;
}

bool						server_parser::set_directives(std::vector<std::string> tokens)
{
	bool res;

	if (tokens[0] == "port")
		res = setPort(tokens);
	else if (tokens[0] == "host")
		res = setHost(tokens);
	else if (tokens[0] == "server_name")
		res = setNames(tokens);
	else if (tokens[0] == "root")
		res = setRoot(tokens);
	else if (tokens[0] == "error_page")
		res = setErrorPages(tokens);
	else if (tokens[0] == "size")
		res = setMaxSize(tokens);
	else
		res = false;	
	return res;
}


 
 server_parser::server_parser(std::vector<std::string> block) : _serverBlock(block)
 {
	setDefault();
	std::vector<std::string> tokens;
	std::vector<std::string>::iterator tmp;

	int in_location = 0;


	std::vector<std::string>::iterator it = _serverBlock.begin() + 1;
	for(; it != _serverBlock.end(); it++)
	{
		if(is_serverline(*it) && *it != "	location" && in_location == 0)
		{
			tokens = ft_split(*it, "	 ");
			if(!set_directives(tokens))
				throw "File Error : set a directive failed !!";
		}
		else if (*it == "	location" || in_location == 1)
		{
			if (in_location == 0)
				in_location = 1;
			tmp = it + 1;
			if ( tmp == _serverBlock.end() || *tmp == "	location")
			{
				_locationBlock.push_back(*it);
				location_parser *obj = new location_parser(_locationBlock);
				_locations.push_back(*obj);
				_locationBlock.clear();
				delete obj;
			}
			else
				_locationBlock.push_back(*it);
		}
		else
			throw ("File Error: line identation not valid !!");
	}
	 
 } 



int							server_parser::getMaxSzie()
{
	return clientMaxBodySize;
}
int							server_parser::getPort()
{
	return port;
}
std::string					server_parser::getHost()
{
	return host;
}
std::string					server_parser::getRoot()
{
	return root_path;
}
std::vector<std::string>	server_parser::getNames()
{
	return names;
}

std::vector<std::string>	server_parser::getErrorPages()
{
	return error_pages;
}

std::vector<std::string>	server_parser::getServerBlock()
{
	return	_serverBlock;
}