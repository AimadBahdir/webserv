# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wben-sai <wben-sai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/20 09:33:47 by wben-sai          #+#    #+#              #
#    Updated: 2022/02/17 15:20:12 by wben-sai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server
SRC = main.cpp

all : $(NAME)

$(NAME):$(SRC)
	clang++ --std=c++98 -Wall -Wextra -Werror $(SRC) -o $(NAME);

clean:
	rm -rf server
fclean:
	rm -rf server
	
re: fclean all