#pragma once

#include "utils.hpp"
#include <fcntl.h>
#include <unistd.h>

class request_parser
{
	private:

		// Directives :
		std::string                         methode;
		std::string                         path;
		std::string                         queries;
		std::string                         version;
		std::map<std::string, std::string>  headers;
		std::string                         bodyFile;
		
		// Variables;
		int									in_body;
		int									status;
		std::string							requestHeader;
		std::string							chunkedBody;
		std::string							reserve;
		size_t								bodyLength;
		int 								isChunked;
		int									stored;

	public:

		request_parser();
		request_parser(std::string path);
		~request_parser();
		request_parser &operator=(request_parser const &src);

		// Getters :
		std::string                         	getMethode();
		std::string                         	getPath();
		std::string                         	getQueries();
		std::string                         	getVersion();
		std::map<std::string, std::string>  	getHeaders();
		std::string                         	getBodyFile();
		int										getStatus();

		// Setters :

		void									sendLine(std::string _line);
		bool									fillRequestHeader(std::string line);
		bool									fillChunkedBody(std::string line);
		bool									set_requestDirectives(std::string token);
		bool									setRequestLine(std::string token);
		bool									setPath(std::string token);
		bool									setVersion(std::string token);
		void 									removeFile();


};