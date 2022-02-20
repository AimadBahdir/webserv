NAME = webserv
SRC = main.cpp responder/*.cpp
FLAGS = -Wall -Wextra -Werror -std=c++98 -g -fsanitize=address

all: $(NAME)

$(NAME):
	@c++ $(FLAGS) $(SRC) -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean: clean

re: fclean all

r: re
	@clear
	@./$(NAME)