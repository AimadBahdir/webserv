# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/20 09:33:47 by wben-sai          #+#    #+#              #
#    Updated: 2022/03/12 15:13:21 by wben-sai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server
SRC = main.cpp sock_server.cpp ../parser/utils.cpp ../parser/parser.cpp ../parser/server_parser.cpp ../parser/location_parser.cpp   ../parser/request_parser.cpp  

all : $(NAME)

$(NAME):$(SRC)
	c++ --std=c++98 -Wall -Wextra -Werror $(SRC) -o $(NAME);

clean:
	rm -rf server
fclean:
	rm -rf server
	
re: fclean all