# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laroges <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 01:52:45 by laroges           #+#    #+#              #
#    Updated: 2023/11/02 17:56:59 by laroges          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c \
	check_access.c \
	clean_memory.c \
	process.c \
	utils.c \
	init.c \
	parsing.c \

CC =	gcc

CFLAGS = -Wall -Werror -Wextra

OBJ =	$(SRC:.c=.o)

NAME =	./pipex

NAMELIBFT =	libft.a

NAMEGNL =	get_next_line.a

INCLUDELIBFT =	./libft/

INCLUDEGNL =	./getnextline/

all: $(NAME)

%.o : %.c pipex.h
	$(CC) $(CFLAGS) -I $(INCLUDELIBFT) -I $(INCLUDEGNL) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	make -C libft
	make -C getnextline
	cp $(INCLUDELIBFT)$(NAMELIBFT) .
	cp $(INCLUDEGNL)$(NAMEGNL) .
	$(CC) $(CFLAGS) $(OBJ) -I $(INCLUDELIBFT) $(NAMELIBFT) -I $(INCLUDEGNL) $(NAMEGNL) -o $(NAME)

clean:
	make clean -C libft
	make clean -C getnextline
	rm -f $(OBJ) $(NAMELIBFT) $(INCLUDELIBFT)$(NAMELIBFT)
	rm -f $(OBJ) $(NAMEGNL) $(INCLUDEGNL)$(NAMEGNL)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
