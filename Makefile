# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 17:29:03 by julrusse          #+#    #+#              #
#    Updated: 2025/01/09 15:41:51 by julrusse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= so_long.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

# Répertoires et fichiers
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx
MLX = $(MLX_DIR)/libmlx.a

INCLUDES = -I includes -I $(LIBFT_DIR) -I $(MLX_DIR)

SRC =	read_map.c \
		utils.c \
		render.c \
		main.c
OBJ = $(SRC:.c=.o)

# Règles principales
all: $(LIBFT) $(MLX) $(NAME)

# Compile la libft
$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR)

# Compile la MiniLibX
$(MLX):
	@echo "Compiling MiniLibX..."
	@$(MAKE) -C $(MLX_DIR)

# Compile le projet
$(NAME): $(OBJ)
	@echo "Creating $(NAME)..."
	@ar rcs $(NAME) $(OBJ) $(LIBFT) $(MLX)
	@ranlib $(NAME)

# Compile les fichiers .c en .o
%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Nettoyage des objets du projet
clean:
	@echo "Cleaning objects..."
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

# Nettoyage complet
fclean: clean
	@echo "Cleaning everything..."
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Recompile tout
re: fclean all

.PHONY: all clean fclean re
