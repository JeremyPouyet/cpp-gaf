##
## Practical alias
##
CC		= g++
RM		= rm -rf

##
## code like a boss
##
CPPFLAGS	+= -W -Wextra -Wall -fPIC
#CPPFLAGS	+= -fmax-errors=2
CPPFLAGS	+= -fopenmp -lboost_system

##
## header location
##
CPPFLAGS += -I./
CPPFLAGS += -I./inih/
CPPFLAGS += -I./libs/

##
## shared library flag
##
LDFLAGS		+= -shared

LIBDL		= -ldl -lgomp

##
## c++ version
##
CPPFLAGS	+= -std=c++11

##
## files generation compilation options
##
NAME	= open-gaf

SRCS	= main.cpp \
	ProblemLoader.cpp \
	Chromosome.cpp \
	Population.cpp \
	Config.cpp \
\
	inih/INIReader.cpp \
	inih/ini.cpp

OBJS	= $(SRCS:.cpp=.o)
	
##
## compilation
##
all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME) $(LIBDL)

##
## Clean data
##
clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re rclean
