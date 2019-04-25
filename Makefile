##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile for do_op
##

CC		:= gcc

NAME		:= ai
TEST_NAME	:= mysh_test

FILES		:= main get_next_line
FILES_TEST	:=  get_next_line

SRC_NAMES	:= $(addsuffix .c, $(FILES))
SRC		:= $(addprefix src/, $(SRC_NAMES))

CINC		:= -I include/
CFLAGS		:= -g -Werror -pedantic -Wall -Wextra -std=c99

OBJ		:= $(SRC:src/%.c=obj/%.o)

RED		:= \033[0;31m
CYAN		:= \033[0;36m
GOLD		:= \033[0;33m
GREEN		:= \033[0;32m
WHITE		:= \033[0;0m

PREFIX2		:= $(CYAN)"[TEST]"
PREFIX		:= $(CYAN)"[$(NAME)]"

all:		createdir $(NAME)

obj/%.o: src/%.c
	@$(CC) -c $(CFLAGS) $(CINC) -o $@ $^
	@echo "$(PREFIX) $(GREEN)$^ $(GOLD)=> $(GREEN)$@"

$(NAME):	$(OBJ)
	@echo "$(PREFIX) $(GOLD)Compiling...$(WHITE)\r"
	@gcc $(OBJ) -o $(NAME) $(CFLAGS) $(CINC)
	@echo "$(PREFIX) $(GOLD)Compiled !$(WHITE)"

clean:
	@echo "$(PREFIX) $(RED)Delete $(GOLD)$(PWD_PATH)/obj/*.o$(WHITE)"
	@rm -rf $(OBJ)

fclean:		clean
	@echo "$(PREFIX) $(RED)Delete $(GOLD)$(PWD)/$(NAME)$(WHITE)"
	@rm -rf $(NAME)
	@rm -rf $(TEST_NAME)

re:		fclean all clean

createdir:
	@mkdir -p obj

unit_test:
	@echo "$(PREFIX2) $(GOLD)Run tests$(WHITE)"
	@gcc -o $(TEST_NAME) $(FILES_TEST) test/tests_my_sh.c $(LDFLAGS) $(CINC) -lcriterion --coverage
	@./$(TEST_NAME)
	@gcovr --exclude tests/
	@echo "$(PREFIX2) $(GOLD)End tests$(WHITE)"
	@rm -rf *.g*
