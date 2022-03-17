#include "request_parser.hpp"

request_parser::request_parser(){
	
	bodyFile = "defaultBody.txt";
	status = 0;
	stored = 0;
	in_body = 0;
	bodyLength = 0;
	isChunked = 0;
}

request_parser::request_parser(std::string path) : bodyFile(path){
	status = 0;
	stored = 0;
	in_body = 0;
	bodyLength = 0;
	isChunked = 0;
}

request_parser::~request_parser(){

}

request_parser      &request_parser::operator=(request_parser const &src)
{
	if (this == &src)
		return *this;

	error =  src.error;
	methode = src.methode;
	path = src.path;
	queries = src.queries;
	version = src.version;
	headers = src.headers;
	bodyFile = src.bodyFile;
	
	in_body = src.in_body;
	status = src.status;
	requestHeader = src.requestHeader;
	chunkedBody = src.chunkedBody;
	reserve = src.reserve;
	bodyLength = src.bodyLength;
	isChunked = src.isChunked;
	stored = src.stored;

	return *this;
}

void				request_parser::removeFile()
{
	int res = -1;
	if(bodyFile != "")
		res = open(bodyFile.c_str(), O_RDONLY);
	if(res != -1)
	{
		if(bodyFile != "" && remove(bodyFile.c_str()) == 0 )
    		std::cout << "File successfully deleted" << std::endl;
		close(res);
	}
    	
}


bool		request_parser::fillRequestHeader(std::string line)
{
	bool res = false;

	requestHeader += line;
	
	size_t pos = requestHeader.find("\r\n\r\n");

	if (pos != std::string::npos)
	{
		reserve += requestHeader.substr(pos + 4);
		requestHeader = requestHeader.substr(0, pos);
		in_body = 1;
		res = true;
	}
	//std::cout << reserve << std::endl;
	// else
	// {
	// 	requestHeader += line;
	// }


	return res;
}

bool		request_parser::fillChunkedBody(std::string line)
{
	bool res= false;

	if(!reserve.empty())
	{
		chunkedBody += reserve;
		reserve.clear();
	}

	chunkedBody += line; 

	size_t pos = chunkedBody.find("0\r\n\r\n");
	
	if(pos != std::string::npos)
	{
		chunkedBody = chunkedBody.substr(0, pos);
		res = true;
	}
	
	return res;
}

bool		request_parser::setPath(std::string token)
{
	std::vector<std::string> tokens = ft_split(token, "?");

	if (tokens.size() < 2)
	{
		path = token;
		return true;
	}
	else
	{
		path = tokens[0];
		queries = tokens[1];
		return true;
	}
	
	return false;
}

bool		request_parser::setVersion(std::string token)
{
	std::vector<std::string> tokens = ft_split(token, "/");

	if(tokens.size() == 2)
		version = tokens[1];
	else
		return false;
	
	return true;
}


bool		request_parser::setRequestLine(std::string token)
{

	std::vector<std::string> tokens = ft_split(token, " ");
	
	if (tokens.size() != 3)
		return false;
	
	if (tokens[0] == "GET" || tokens[0] == "POST" || tokens[0] == "DELETE")
		methode = tokens[0];
	else
		return false;

	if (!setPath(tokens[1]))
		return false;
	
	if(!setVersion(tokens[2]))
		return false;

	return true;	
}



bool		request_parser::set_requestDirectives(std::string	token)
{

	size_t pos = token.find(": ");

	if(pos != std::string::npos)
	{
		std::string headkey = token.substr(0, pos);
		std::string value =  token.substr(pos + 2);

		headers[headkey] = value;
		if(headkey == "Content-Length")
			bodyLength = atoi(value.c_str());
		
		if(headkey == "Transfer-Encoding")
			isChunked = 1;

	}
	else
		return false;
	return true;
}



void				request_parser::sendLine(std::string _line)
{
	if (in_body == 0)
	{
		if (fillRequestHeader(_line))
		{
			_line.clear(); // case 1;
			std::vector<std::string> tokens = ft_split(requestHeader, "\r\n");
			std::vector<std::string>::iterator it = tokens.begin();

			if (!setRequestLine(*it))
				throw "Request Error: Request Line failed !!";
			it++;
			for(; it < tokens.end(); it++)
			{
				if(!set_requestDirectives(*it))
					throw "Request Error: Set Request Header failed !!";
			}
			if((methode == "GET") || (isChunked == 0 && bodyLength == 0))
			{
				status = 1;
				return ;
			}
		}


		// if(in_body == 1)
		// {
		// 	if(bodyLength != 0)
		// 		// 
		// 	else if(isChunked == 1)
		// 		//
		// }
	}
	if(in_body == 1)
	{
		if (bodyLength != 0)
		{
			std::fstream file;
			
			file.open(bodyFile, std::ios::app);
			if(file.is_open())
			{
				if(!reserve.empty())
				{
					_line = reserve + _line;
					reserve.clear();
				}
				if((_line.length() + stored) >= bodyLength)
				{
					_line = _line.substr(0, (bodyLength - stored));
					status = 1;
				}
				file << _line;
				stored += _line.length();
				file.close();
			}

		}
		else if (isChunked == 1)
		{
			if(fillChunkedBody(_line))
			{
				status = 1;
				std::vector<std::string> tokens = ft_split(chunkedBody, "\r\n");
				std::vector<std::string>::iterator it = tokens.begin();

				std::fstream file;

				file.open(bodyFile, std::ios::out);
				if(file.is_open())
				{
					for(; it != tokens.end(); it++)
					{
						if(!is_hexa(*it))
							file << *it;
					}
					file.close();
				}
			}
		}
	}

}


