#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <stdio.h>


std::vector<std::string>        ft_split(std::string str, std::string delim);
bool                            is_empty(std::string str);
void                            print_vector(std::vector<std::string> vc);
bool                            is_serverline(std::string str);
bool                            is_locationline(std::string str);
bool                            is_digit(std::string str);
bool                            is_directive(std::string str);
bool                            is_validefile(std::string str);
bool                            is_hexa(std::string str);