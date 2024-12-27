CXX = g++
CXXFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -Iinc/
SRCS = src/Server.cpp
OBJS = $(SRCS:.c=.o)
NAME = ircserv
RM = rm -rf

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
$(OBJS): %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	$(RM) $(NAME)
fclean: clean
	$(RM) $(OBJS)
re: fclean all
