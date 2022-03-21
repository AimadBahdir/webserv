NAME = webserv
SRC = main.cpp ./server/sock_server.cpp ./responder/responder.cpp ./parser/utils.cpp ./parser/parser.cpp ./parser/server_parser.cpp ./parser/location_parser.cpp ./parser/request_parser.cpp 
FLAGS = -Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME):
	@c++ $(FLAGS) $(SRC) -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean: clean

re: fclean all

r: re
	@./webserv file.conf