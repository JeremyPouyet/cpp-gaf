##
## Practical alias
##
CC		= g++
RM		= rm -rf
SRCS_DIR	= ./srcs

##
## code like a boss
##
CPPFLAGS	+= -W -Wextra -Wall -fPIC
CPPFLAGS	+= -fopenmp -lboost_system

##
## header location
##
CPPFLAGS += -I./srcs/algorithm -I./srcs/utils
CPPFLAGS += -I./srcs/problem -I./inih/ -I./libs/

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

SRCS	= $(SRCS_DIR)/main.cpp \
	$(SRCS_DIR)/algorithm/Chromosome.cpp \
	$(SRCS_DIR)/algorithm/Population.cpp \
	$(SRCS_DIR)/algorithm/Simulation.cpp \
	$(SRCS_DIR)/utils/Config.cpp \
\
	$(SRCS_DIR)/inih/INIReader.cpp \
	$(SRCS_DIR)/inih/ini.cpp

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
