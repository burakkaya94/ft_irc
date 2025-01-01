CXX = c++
CXXFLAGS = -Wall -Wextra
CPPFLAGS = -Iinc/
SRCS = main.cpp src/Server.cpp src/Channel.cpp src/User.cpp
OBJS = $(SRCS:.cpp=.o)
NAME = ircserv
RM = rm -rf

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OBJS) -o $(NAME)
$(OBJS): %.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
clean:
	$(RM) $(NAME)
fclean: clean
	$(RM) $(OBJS)
re: fclean all
