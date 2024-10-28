CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -Wpedantic -Ofast
NAME = PmergeMe.out
MAKEFLAGS = --no-print-directory

SRC =	srcs/main.cpp\
		srcs/node.cpp\
		srcs/nodeList.cpp\
		srcs/PmergeMe.cpp

OBJ = $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
