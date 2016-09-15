# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lgarczyn <lgarczyn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/01/22 17:11:22 by lgarczyn          #+#    #+#              #
#    Updated: 2016/09/15 13:03:27 by lgarczyn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in

SRC =	lemin.c \
		parse.c \
		link.c \
		check.c \
		path.c \
		solve.c \
		display.c

OBJ = $(SRC:.c=.o)

INC = -I libft/includes

LIB = -L libft/ -lft

DEB =

OPT = -Ofast -funsigned-char

FLG = -Wall -Wextra -Werror $(OPT) $(DEB)

all: $(NAME)

libft.a:
	cd libft && make all

$(NAME):$(OBJ) libft.a
	gcc $(OBJ) $(FLG) $(LIB) -o $(NAME)

%.o: %.c
	gcc $(INC) $(FLG) -c $< $

clean:
	rm -rf $(OBJ)
	cd libft && make clean

fclean: clean
	rm -rf $(NAME)
	cd libft && make fclean

re: fclean all

fcleannolib:
	rm -rf $(OBJ)
	rm -rf $(NAME)

smart: fcleannolib all
