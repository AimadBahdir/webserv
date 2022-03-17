#include "utils.hpp"
#include "request_parser.hpp"

int     main()
{

	// std::string str = "Accept-Encoding: ";

	// size_t pos = str.find(": ");

	// if(pos != std::string::npos)
	// {
	// 	std::cout << pos << std::endl;
	// 	std::cout << "First = " << str.substr(0, pos) << std::endl;
	// 	std::cout << "Second = " << str.substr(pos + 2) << std::endl;
		
	// }

	//std::string s = "POST / HTTP/1.1\r\nContent-Type: text/html\r\nContent-Length: 680\r\n\r\n<html><head><title></title></head><body><h1>Hello</h1></body></html>";
	std::string str = "POST /path?query1=val&query2=val&query3=val&query4=val HTTP/1.1\r\n";
	std::string str2 = "headkey1: value\r\nheadkey2: value\r\nheadkey3: value\r\nheadkey4: value\r\n\r\n";
	// std::string str3 = "Content-Length: 88\r\nheadkey5: value5\r\n\r\nBoooobiiiz Bobiiiiiz";
	// std::string str4 = "\nreserve rfgdsfgdsfgsdfgve";
	//std::string str3 = "\r\nTransfer-Encoding: chunked\r\n\r\n26\r\nVoici les données du premier morceau\r\n";

	request_parser obj("filebody.txt");
	//std::cout << obj.getStatus() << std::endl;
	try {
		// obj.sendLine(s);
		// obj.sendLine("Pluuuuus");
		//obj.sendLine("Test");
		//if(!obj.getStatus())
			obj.sendLine(str);
		//if(!obj.getStatus())
			obj.sendLine(str2);
		// obj.sendLine(str3);
		// obj.sendLine(str4);
		// obj.sendLine("26\r\nVoici les données du deuxieme morceau\r\n");
		// obj.sendLine("1C\r\net voici un second morceau\r\n");
		// obj.sendLine("12\r\nsans saut de ligne\r\n0\r\n\r\n");


		//std::cout<< obj.getStatus() << std::endl;
		//if(!obj.getStatus())
			obj.sendLine("\n1body body body body body body body body body body body body body body body body body1\n");
		std::cout<< obj.getStatus() << std::endl;
		std::cout << "METHOD: " << obj.getMethode(); 
		// obj.sendLine("\n2body body body body body body body body body body body body body body body body body2\n");
		// std::cout<< obj.getStatus() << std::endl;

		// obj.sendLine("\n3body body body body body body body body body body body body body body body body body3\n");
		//obj.sendLine("\n4body body body body body body body body body body body body body body body body body4\n");
	}
	catch(const char *str)
	{
		std::cout << str << std::endl;
	}
	//std::cout << obj.getStatus() << std::endl;
	
	//std::cout << obj.getHeaders()["Content-Length"] << std::endl;

	//std::vector<std::string> tokens = ft_split(obj.requestHeader, "\r\n");
	//print_vector(tokens);

	//std::cout << "================\n" << obj.reserve << "\n===============\n";

	// std::cout << obj.getVersion() << std::endl;
	//std::cout << obj.getHeaders()["Content-Length"] << std::endl;

	return 0;
}	