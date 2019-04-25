##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Makefile
##

GCC=            gcc

SRC=		ai.c

LIB=		-Llib/my/ -lmy

INC=            -I./include

CSFML=		-lcsfml-graphics -lcsfml-audio -lcsfml-window -lcsfml-system

OBJ=            $(SRC:.c)

NAME=          	ai

all:            $(NAME)

$(NAME):
		make -C ./lib/my
		$(GCC) -g $(SRC) $(LIB) $(INC) $(CSFML) -o $(NAME)

clean:
		rm -f *~ *#

fclean:         clean
		rm $(NAME) libmy.a

re:	fclean all clean
