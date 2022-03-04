NAME = webserv
SRC = main.cpp responder/responder.cpp
FLAGS = -Wall -Wextra -Werror -std=c++98 -fsanitize=address

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