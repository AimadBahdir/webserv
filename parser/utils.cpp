#include "utils.hpp"



std::vector<std::string>        ft_split(std::string str, std::string delim)
{
	std::vector<std::string> tokens;

	char *ptr = strtok((char *)str.c_str(), delim.c_str());
	
	while(ptr != NULL)
	{
		tokens.push_back(ptr);
		ptr = strtok(NULL, delim.c_str());
	}

	return tokens;
}

bool                            is_empty(std::string str)
{
	if (str.empty())
		return true;
	for(size_t i = 0; i < str.length() ; i++)
	{
		if (str[i] != 32 && str[i] != 9)
			return false;
	}
	return true;
}


void		print_vector(std::vector<std::string> vc)
{
	std::vector<std::string>::iterator it = vc.begin();
	for(;it != vc.end(); it++)
		std::cout << *it << std::endl;
}

bool                            is_serverline(std::string str)
{
	if(str[0] == 9 && str[1] != 9 && str[1] != 32)
		return true;
	return false;
}

bool                            is_locationline(std::string str)
{
	if(str[0] == 9 && str[1] == 9 && str[2] != 9 && str[2] != 32)
		return true;
	return false;
}

bool                            is_digit(std::string str)
{
	for(size_t i = 0; i < str.length(); i++)
	{
		if (str[i] < 48 || str[i] > 57)
			return false;
	}
	return true;
}


bool							is_directive(std::string str)
{
	if (str == "port" || str == "host" ||  str == "server_name" ||  str == "root" ||  str == "error_page" ||  str == "location" ||  str == "size")
		return true;
	return false;
}

bool                            is_validefile(std::string str)
{
	int len = str.length();
	if (len < 6)
		return false;
	if(str[len - 1] != 'f'  || str[len - 2] != 'n' || str[len - 3] != 'o' || str[len - 4] != 'c' || str[len - 5] != '.')
		return false;
	return true;
}


bool                            is_hexa(std::string str)
{
	size_t i = 0;
	size_t len = str.length();

	while(i < len)
	{
		if ((str[i] >= 48 && str[i] <= 57) || (str[i] >= 65 && str[i] <= 70))
			i++;
		else
			return false;
	}
	return true;
}














