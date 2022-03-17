#include "parser.hpp"



parser &parser::operator=(parser const &src)
{
	if (this == &src)
		return *this;
	_block = src._block;
	_line = src._line;

	return *this;
}

parser::parser(std::string av)
{
	std::fstream	_file;
	bool 			in_block = 0;

	if(!is_validefile(av))
		throw "File Error : the file format must be .conf";
	_file.open(av, std::ios::in);
	if(_file.is_open())
	{
		while (getline(_file, _line))
		{
			if (_line != "server" && !is_empty(_line) && in_block == 0)
				throw "File Error : you must start with server !!";
			if(_line == "server" || in_block == 1)
			{
				if (is_empty(_line) && in_block == 1)
				{
					server_parser *obj = new server_parser(_block);
					_servers.push_back(*obj);
					in_block = 0;
					_block.clear();
					delete obj;
				}
				else
				{
					if(in_block == 0)
						in_block = 1;
					_block.push_back(_line);
				}
			}
		}
		if (in_block == 1)
		{
			server_parser *obj = new server_parser(_block);
			_servers.push_back(*obj);
			in_block = 0;
			_block.clear();
			delete obj;
		}
		_file.close();
	}
	else
	{
		throw "File Error: open config file failed !!";
	}

}

parser::parser(){}
parser::~parser(){}


void    parser::display()
{
	std::vector<std::string>::iterator it = _block.begin();
	for(;it != _block.end(); it++)
		std::cout << *it << std::endl;
}
