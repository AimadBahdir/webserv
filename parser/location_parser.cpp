#include "location_parser.hpp"

location_parser::location_parser()
{

}

location_parser::~location_parser()
{

}

location_parser &location_parser::operator=(location_parser const &src){
	if(this == &src)
		return *this;
	auto_index = src.auto_index;
	location_path = src.location_path;
	root_path = src.root_path;
	upload_path = src.upload_path;
	cgi_path = src.cgi_path;
	accepted_requests = src.accepted_requests;
	index = src.index;
	redirection = src.redirection;
	_locationBlock = src._locationBlock;

	return *this;

}


void		location_parser::setLocationDefault()
{
	auto_index = false;
	accepted_requests.push_back("GET");
	accepted_requests.push_back("DELETE");
	accepted_requests.push_back("POST");

	lid.index = 0;
	lid.auto_index = 0;
	lid.location_path = 0;
	lid.root_path = 0;
	lid.upload_path = 0;
	lid.cgi_path = 0;
	lid.accepted_requests = 0;
	lid.redirection = 0;
}


bool		location_parser::setAutoIndex(std::vector<std::string> tokens)
{
	if(tokens.size() != 2)
		return false;
	if (tokens[1] == "on")
		auto_index = true;
	else if (tokens[1] == "off")
		auto_index = false;
	else
		return false;
	
	lid.auto_index++;
	if (lid.auto_index > 1)
		return false;
	
	return true;
}

bool		location_parser::setLocationPath(std::vector<std::string> tokens)
{
	if(tokens.size() != 2)
		return false;
	if (tokens[1][0] != '.' && tokens[1][0] != '/')
		return false;

	location_path = tokens[1];
	
	lid.location_path++;
	if (lid.location_path > 1)
		return false;
	
	return true;
}

bool		location_parser::setRootPath(std::vector<std::string> tokens)
{
	if(tokens.size() != 2)
		return false;
	root_path = tokens[1];

	lid.root_path++;
	if (lid.root_path > 1)
		return false;

	return true;
}

bool		location_parser::setUploadPath(std::vector<std::string> tokens)
{
	if(tokens.size() != 2)
		return false;
	upload_path = tokens[1];

	lid.upload_path++;
	if (lid.upload_path > 1)
		return false;

	return true;
}

bool		location_parser::setCgiPath(std::vector<std::string> tokens)
{
	if(tokens.size() != 2)
		return false;
	cgi_path = tokens[1];

	lid.cgi_path++;
	if (lid.cgi_path > 1)
		return false;
	return true;
}

bool		location_parser::setAcceptedRequeasts(std::vector<std::string> tokens)
{
	if(tokens.size() < 2 || tokens.size() > 4)
		return false;
	
	std::vector<std::string>::iterator it = tokens.begin() + 1;

	accepted_requests.clear();
	for(; it != tokens.end() ; it++)
	{
		if (*it != "GET" && *it != "DELETE" && *it != "POST")
			return false;
		accepted_requests.push_back(*it);
	}

	lid.accepted_requests++;
	if (lid.accepted_requests > 1)
		return false;

	return true;
}

bool		location_parser::setIndex(std::vector<std::string> tokens)
{
	if (tokens.size() < 2)
		return false;
	
	std::vector<std::string>::iterator it = tokens.begin() + 1;

	for(; it != tokens.end() ; it++)
		index.push_back(*it);
	
	lid.index++;
	if (lid.index > 1)
		return false;

	return true;
}

bool		location_parser::setRedirection(std::vector<std::string> tokens)
{
	if (tokens.size() != 3)
		return false;
	if (!is_digit(tokens[1]))
		return false;

	redirection = std::make_pair(tokens[1], tokens[2]);

	lid.redirection++;
	if(lid.redirection > 1)
		return false;

	return true;
}




bool	location_parser::set_locationdirectives(std::vector<std::string> tokens)
{
	bool res;

	if (tokens[0] == "auto_index")
		res = setAutoIndex(tokens);
	else if (tokens[0] == "location_path")
		res = setLocationPath(tokens);
	else if (tokens[0] == "root")
		res = setRootPath(tokens);
	else if (tokens[0] == "upload")
		res = setUploadPath(tokens);
	else if (tokens[0] == "cgi")
		res = setCgiPath(tokens);
	else if (tokens[0] == "requests")
		res = setAcceptedRequeasts(tokens);
	else if (tokens[0] == "index")
		res = setIndex(tokens);
	else if (tokens[0] == "return")
		res = setRedirection(tokens);
	else
		res = false;	
	return res;
}

location_parser::location_parser(std::vector<std::string> block) : _locationBlock(block)
{
	setLocationDefault();
	std::vector<std::string>                tokens;
	
	std::vector<std::string>::iterator      it = _locationBlock.begin() + 1;
	for(; it != _locationBlock.end(); it++)
	{
		if(is_locationline(*it))
		{
			tokens = ft_split(*it, "	 ");
			if(!set_locationdirectives(tokens))
				throw "File Error : set a location directive failed !!";
		}
		else
			throw ("File Error: location line identation not valid !!");
	}
	if (lid.location_path != 1)
		throw "File Error : set a location_path is mandatory !!";
}


bool							location_parser::getAutoIndex()
{
	return (auto_index);
}
std::string						location_parser::getLocationPath()
{
	return	(location_path);
}
std::string						location_parser::getRootPath()
{
	return (root_path);
}

std::string						location_parser::getUploadPath()
{
	return	(upload_path);
}

std::string						location_parser::getCgiPath()
{
	return (cgi_path);
}

std::vector<std::string>		location_parser::getAcceptedRequeasts()
{
	return (accepted_requests);
}

std::vector<std::string>		location_parser::getIndex()
{
	return (index);
}

std::pair<std::string, std::string>		location_parser::getRedirection()
{
	return (redirection);
}