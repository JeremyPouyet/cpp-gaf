##
## Practical alias
##
CC		= g++
RM		= rm -f

##
## code like a boss
##
CPPFLAGS	+= -W -Wextra -Wall

CPPFLAGS	+= -fmax-errors=2

##
## c++ version
##
CPPFLAGS	+= -std=c++11

##
## files generation compilation options
##
NAME	= equation_finder

SRCS	= main.cpp \
	Chromosome.cpp \
	Population.cpp \

OBJS	= $(SRCS:.cpp=.o)

##
## compile
##
all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) -o $(NAME) $(OBJS) $(LIBS)

##
## Clean useless datas
##
clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re rclean
