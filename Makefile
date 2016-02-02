##
## Practical alias
##
CC		= g++
RM		= rm -rf

##
## code like a boss
##
CPPFLAGS	+= -W -Wextra -Wall -fPIC
#CPPFLAGS	+= -rdynamic -export-dynamic
CPPFLAGS	+= -fmax-errors=2

##
## header location
##
CPPFLAGS += -I./
CPPFLAGS += -I./inih/

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
P1	= problems/equation/EquationProblem.so
P2	= problems/range/RangeProblem.so


SRCS	= main.cpp \
	ProblemLoader.cpp \
	AProblem.cpp \
	Chromosome.cpp \
	Population.cpp \
	Config.cpp \
\
	inih/INIReader.cpp \
	inih/ini.cpp 

SRCS_P1	= problems/equation/EquationProblem.cpp

SRCS_P2 = problems/range/RangeProblem.cpp

OBJS	= $(SRCS:.cpp=.o)
OBJS_P1 = $(SRCS_P1:.cpp=.o)
OBJS_P2 = $(SRCS_P2:.cpp=.o)

##
## compilation
##
all:		$(NAME) $(P1) $(P2)

$(P1):		$(OBJS_P1)
		$(CC) $(LDFLAGS) $(OBJS_P1) -o $(P1)

$(P2):		$(OBJS_P2)
		$(CC) $(LDFLAGS) $(OBJS_P2) -o $(P2)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LIBDL)

##
## Clean data
##
clean:
		$(RM) $(OBJS) $(OBJS_P1) $(OBJS_P2)

fclean:		clean
		$(RM) $(NAME) $(P1) $(P2)

re:		fclean all

.PHONY:		all clean fclean re rclean
