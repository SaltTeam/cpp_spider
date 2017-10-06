##
## Makefile for cpp_spider in /home/delacr_a/rendu/CPP/cpp_spider
## 
## Made by Maxence Delacroix
## Login   <delacr_a@epitech.net>
## 
## Started on  Fri Oct  6 15:48:25 2017 Maxence Delacroix
## Last update Fri Oct  6 15:52:18 2017 Maxence Delacroix
##

INCLUDE	=	-I./includes/

RM	=	rm -rf

SERVER	=	cpp_spider_server

CLIENT	=	cpp_spider_client

CPPFLAGS	+=	-W -Wall -Wextra -Werror -std=c++14 -MD -MP $(INCLUDE)

LDFLAGS	+=	 -lssl -lboost_system -lboost_thread -lcrypto -lm -lsqlite3

CC	=   g++

DEBUG	?=  0

ifeq	($(DEBUG), 1)
	CC		=	g++
	CPPFLAGS	+=	-g -ggdb3
endif

SOURCES		=	sources/

DATABASE	=	$(SOURCES)Database/

LOGGER		=	$(SOURCES)logger/

NETWORK		=	$(SOURCES)Network/

PROTOCOL	=	$(SOURCES)Protocol/

S_SRCS	=	$(SOURCES)ServerCore.cpp \
		$(SOURCES)ServerMain.cpp \
		$(DATABASE)Sqlite.cpp \
		$(LOGGER)Logger.cpp \
		$(PROTOCOL)Buffer.cpp \
		$(PROTOCOL)Serializer.cpp \
		$(PROTOCOL)ServerProtocol.cpp \
		$(NETWORK)ServerNetwork.cpp

S_OBJS	=	$(S_SRCS:.cpp=.o)

S_DEPS	=	$(S_SRCS:.cpp=.d)

all:	$(SERVER)

$(SERVER):	$(S_OBJS)
	$(CC) -o $(SERVER) $(S_OBJS) $(LDFLAGS)

%.o:	%.cpp
	$(CC) -c -o $@ $< $(CPPFLAGS)

clean:
	$(RM) $(S_OBJS) $(S_DEPS)

fclean:	clean
	$(RM) $(SERVER) $(CLI)

re:	fclean
	@$(MAKE) all

.PHONY: all clean fclean re

-include	$(S_DEPS)
