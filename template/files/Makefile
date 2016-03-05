##
## Practical alias
##
CC		= g++
RM		= rm -rf

##
## code like a boss
##
CPPFLAGS	+= -W -Wextra -Wall -fPIC -fopenmp
CPPFLAGS	+= -fmax-errors=2
CPPFLAGS	+= -I./ -I../../libs/ -I../../srcs/problem/

##
## shared library flag
##
LDFLAGS		+= -shared

LIBDL		= -ldl

##
## c++ version
##
CPPFLAGS	+= -std=c++11

##
## files generation compilation options
##
NAME	= ./problem.so

# add your sources here
SRCS	= ./__CLASS__.cpp

OBJS	= $(SRCS:.cpp=.o)

##
## compilation
##
all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)

##
## Clean data
##
clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)
re:		fclean all

.PHONY:		all clean fclean re rclean