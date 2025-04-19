# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/06 22:46:08 by jgomez-d          #+#    #+#              #
#    Updated: 2025/04/19 02:21:36 by jgomez-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
MLXDIR = minilibx-linux
MLXLIB = $(MLXDIR)/libmlx_Linux.a
CFLAGS  = -Wall -Wextra -Werror -O3 -flto
#-g -fsanitize=address,leak
SRC = fractol.c init.c aux_functions.c draw.c color.c hooks.c hooks_utils.c

OBJ = $(SRC:.c=.o)

LIB = -L$(MLXDIR) -lmlx -lXext -lX11 -lm
all: $(MINILIBX) $(NAME) 

$(MLXLIB):
	@make -C $(MLXDIR)

$(NAME): $(OBJ) $(MLXLIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)
	
%.o: %.c $(MINILIBX)
	$(CC) $(CFLAGS) -I$(MLXLIB) -c $< -o $@

clean:
	@rm -f $(OBJ) 
	@make -C $(MLXDIR) clean

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re