# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgomez-d <jgomez-d@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/06 22:46:08 by jgomez-d          #+#    #+#              #
#    Updated: 2025/04/07 01:31:01 by jgomez-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
MLXDIR = minilibx-linux
MLXLIB = $(MLXDIR)/libmlx_Linux.a
CFLAGS  = -Wall -Wextra -Werror -g 
#-fsanitize=address,leak
SRC = fractol.c init.c aux_functions.c

OBJ = $(SRC:.c=.o)

LIB = -L$(MLXDIR) -lmlx -lXext -lX11 -lm
all: $(MINILIBX) $(NAME) 

$(MLXLIB):
	@make -C $(MLXDIR)

$(NAME): $(OBJ) $(MLXLIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)
#	%.o: %.c $(MINILIBX)
#		$(CC) $(CFLAGS) -I$(MINILIBX) -c $< -o $@
clean:
	@rm -f $(OBJ) 
	@make -C $(MLXDIR) clean

fclean: clean
	@rm -f $(NAME) $(CHEKER)
	@make fclean -C $(MLXDIR)

re: fclean all

.PHONY: all clean fclean re