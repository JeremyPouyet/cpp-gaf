##
## Practical alias
##
CC		= g++
RM		= rm -rf

##
## code like a boss
##
CPPFLAGS	+= -W -Wextra -Wall -fPIC -fopenmp
CPPFLAGS	+= -I./

##
## c++ version
##
CPPFLAGS	+= -std=c++11

##
## files generation compilation options
##
NAME	= ./generator

# add your sources here
SRCS	= generator.cpp

OBJS	= $(SRCS:.cpp=.o)

##
## compilation
##
all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME)

##
## Clean data
##
clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)
re:		fclean all

.PHONY:		all clean fclean re rclean