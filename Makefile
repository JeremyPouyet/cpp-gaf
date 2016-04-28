##
## Practical aliases
##
CC		= g++
RM		= rm -rf
SRCS_DIR	= ./srcs

##
## code like a boss
##
CPPFLAGS	+= -W -Wextra -Wall -fPIC

##
## libraries
##
CPPFLAGS	+= -fopenmp -lboost_system
LIBDL		= -ldl -lgomp

##
## header location
##
CPPFLAGS 	+= -I./srcs/algorithm -I./srcs/utils
CPPFLAGS 	+= -I./srcs/problem -I./inih/ -I./libs/

##
## shared library flag
##
LDFLAGS		+= -shared

##
## c++ version
##
CPPFLAGS	+= -std=c++11

##
## compilation options
##
FRAMEWORK	= open-gaf
PROBLEMS	= $(shell find problems/ -maxdepth 1 -mindepth 1 -type d)
GENERATOR	= template

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
all:		$(FRAMEWORK) $(PROBLEMS) $(GENERATOR)

framework:	$(FRAMEWORK)
$(FRAMEWORK):	$(OBJS)
		$(CC) $(OBJS) -o $(FRAMEWORK) $(LIBDL)

problems: 	$(PROBLEMS)
$(PROBLEMS):
		$(MAKE) -C $@

generator:	$(GENERATOR)
$(GENERATOR):
		$(MAKE) -C $@
##
## Clean
##
RM_OBJS	= $(OBJS) \
	$(foreach dir, $(PROBLEMS), $(wildcard $(dir)/*.o)) \
	$(foreach dir, $(GENERATOR), $(wildcard $(dir)/*.o))

RM_BIN	= $(FRAMEWORK) \
	$(foreach dir, $(PROBLEMS), $(wildcard $(dir)/*.so)) \
	$(GENERATOR)/generator

clean:
	$(RM) $(RM_OBJS)

fclean:	clean
	$(RM) $(RM_BIN)

re:	fclean all

##
## avoid problems
##
.PHONY:	all clean fclean re rclean problems generator \
	$(PROBLEMS) $(FRAMEWORK) $(GENERATOR)
