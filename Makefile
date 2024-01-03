# l**************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: laroges <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/24 01:52:45 by laroges           #+#    #+#              #
#    Updated: 2024/01/03 20:32:49 by laroges          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =	main.c \
	clean_memory.c \
	process.c \
	utils.c \
	init.c \
	parsing.c \
	pipex.c \

CC =	gcc

CFLAGS = -Wall -Werror -Wextra -g3

OBJ =	$(SRC:.c=.o)

NAME =	./pipex

NAMEPRINTF =	libftprintf.a

NAMELIBFT =	libft.a

NAMEGNL =	get_next_line.a

INCLUDEPRINTF =	./ft_printf/

INCLUDELIBFT =	./libft/

INCLUDEGNL =	./getnextline/

all: $(NAME)

%.o : %.c pipex.h
	$(CC) $(CFLAGS) -I $(INCLUDEPRINTF) -I $(INCLUDELIBFT) -I $(INCLUDEGNL) -c $< -o $(<:.c=.o)

$(NAME): $(OBJ)
	make -C ft_printf
	make -C libft
	make -C getnextline
	cp $(INCLUDEPRINTF)$(NAMEPRINTF) .
	cp $(INCLUDELIBFT)$(NAMELIBFT) .
	cp $(INCLUDEGNL)$(NAMEGNL) .
	$(CC) $(CFLAGS) $(OBJ) -I $(INCLUDEPRINTF) $(NAMEPRINTF) -I $(INCLUDELIBFT) $(NAMELIBFT) -I $(INCLUDEGNL) $(NAMEGNL) -o $(NAME)

clean:
	make clean -C ft_printf
	make clean -C libft
	make clean -C getnextline
	rm -f $(OBJ) $(NAMEPRINTF) $(INCLUDEPRINTF)$(NAMEPRINTF)
	rm -f $(OBJ) $(NAMELIBFT) $(INCLUDELIBFT)$(NAMELIBFT)
	rm -f $(OBJ) $(NAMEGNL) $(INCLUDEGNL)$(NAMEGNL)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
