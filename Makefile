# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obamzuro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/04 22:45:06 by obamzuro          #+#    #+#              #
#    Updated: 2018/09/27 12:38:40 by obamzuro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SRCNAME = 	main.c\
			line_drawer.c\
			parser.c

FLAGS = -g

SRC = $(addprefix source/, $(SRCNAME))

OBJ = $(SRC:.c=.o)

HDRDIR = minilibx_macos		\
		 header

HDR = header/fdf.h

all: lib $(NAME)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(FLAGS) $(addprefix -I, $(HDRDIR)) -L libft -lft -lmlx -L minilibx_macos -framework OpenGL -framework AppKit $(SRC)

%.o: %.c $(HDR)
	gcc $(FLAGS) $(addprefix -I, $(HDRDIR)) -c $< -o $@

lib:
	make -C libft

clean:
	make -C libft clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft fclean
	rm -rf $(NAME)

re: fclean all
