NAME = webserv
SRC = main.cpp responder/responder.cpp ../parser/utils.cpp ../parser/parser.cpp ../parser/server_parser.cpp ../parser/location_parser.cpp
FLAGS = -Wall -Wextra -Werror #-std=c++98 -fsanitize=address -g

all: $(NAME)

$(NAME):
	@c++ $(FLAGS) $(SRC) -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean: clean

re: fclean all

r: re
	@clear
	@./$(NAME) file.conf


#func1()
	# check for cgi
		# run request with cgi
	# check for index
		#check for cgi
			#run request with cgi
		#run request
	# check for autoindex
		#run request
	# 403 forbidden

# is directory
	# find location
		# check for root path
			
# is file
	# check for cgi
		# run request with cgi
	# run request