##
## Practical alias
##
CC		= g++
RM		= rm -f

##
## code like a boss
##
CPPFLAGS	+= -W -Wextra -Wall -fPIC

CPPFLAGS	+= -fmax-errors=2

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
NAME	= equation_finder
LIB     = EquationProblem.so


SRCS	= main.cpp \
	Chromosome.cpp \
	Population.cpp \
	
SRC_LIB= EquationProblem.cpp

OBJS	= $(SRCS:.cpp=.o)
LIB_OBJS= $(SRC_LIB:.cpp=.o)

##
## compilation
##
all:		$(LIB) $(NAME)

$(LIB):		$(LIB_OBJS)
		$(CC) $(LDFLAGS) $(LIB_OBJS) -o $(LIB)   

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LIBDL)

##
## Clean data
##
clean:
		$(RM) $(OBJS) $(LIB_OBJS)

fclean:		clean
		$(RM) $(NAME) $(LIB)

re:		fclean all

.PHONY:		all clean fclean re rclean
