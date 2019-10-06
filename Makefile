##
## Makefile for PacketSniffer in /home/nicolas.lemaire/Projet/PacketSniffer
##
## Made by Nicolas Lemaire
## Login   <nicolas.lemaire@epitech.eu>
##
## Started on  Mon Jun  4 10:03:24 2018 Nicolas Lemaire
## Last update Mon Jun  4 10:03:24 2018 Nicolas Lemaire
##

CC	=	gcc

RM	=	rm -f

CFLAGS	=	-Wextra -Wall -I $(INC)

LDFLAGS	=

INC	=	include

NAME	=	AnalyseurPaquets

OBJS	=	$(SRCS:.c=.o)

SRCS	=	src/main.c		\
		src/handlers.c		\
		src/print_headers.c

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
