## Created by maxence.delacroix@epitech.eu the 06/10/2017

INCLUDE	=	-I./includes/

RM	=	rm -rf

SERVER	=	cpp_spider_server

CLIENT	=	cpp_spider_client

CPPFLAGS	+=	-W -Wall -Wextra -Werror -std=c++14 -MD -MP $(INCLUDE) -lssl

LDFLAGS	+=	\

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
		$(NETWORK)ServerNetwork.cpp \
		$(PROTOCOL)Buffer.cpp \
		$(PROTOCOL)Serializer.cpp \
		$(PROTOCOL)ServerProtocol.cpp

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
