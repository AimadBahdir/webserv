#pragma once

#include "utils.hpp"

struct lid {

	int		index;
	int		auto_index;
	int		location_path;
	int		root_path;
	int		upload_path;
	int		cgi_path;
	int		accepted_requests;
	int		redirection;

};

class location_parser
{
	private :
		bool									auto_index;
		std::string								location_path;
		std::string								root_path;
		std::string								upload_path;
		std::string								cgi_path;
		std::vector<std::string>				accepted_requests;
		std::vector<std::string>				index;
		std::pair<std::string, std::string>		redirection;

		std::vector<std::string>				_locationBlock;
		struct lid								lid;


	public :

		
		// Constructors and overloads :

		location_parser();
		location_parser(std::vector<std::string> block);
		~location_parser();
		

		location_parser &operator=(location_parser const &src);

		// Setters :
		bool		setAutoIndex(std::vector<std::string> tokens);
		bool		setLocationPath(std::vector<std::string> tokens);
		bool		setRootPath(std::vector<std::string> tokens);
		bool		setUploadPath(std::vector<std::string> tokens);
		bool		setCgiPath(std::vector<std::string> tokens);
		bool		setAcceptedRequeasts(std::vector<std::string> tokens);
		bool		setIndex(std::vector<std::string> tokens);
		bool		setRedirection(std::vector<std::string> tokens);

		void		setLocationDefault();
		bool		set_locationdirectives(std::vector<std::string> tokens);

		// Getters :
		
		bool									getAutoIndex();
		std::string								getLocationPath();
		std::string								getRootPath();
		std::string								getUploadPath();
		std::string								getCgiPath();
		std::vector<std::string>				getAcceptedRequeasts();
		std::vector<std::string>				getIndex();
		std::pair<std::string, std::string>		getRedirection();
};