# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: julrusse <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 17:29:03 by julrusse          #+#    #+#              #
#    Updated: 2025/01/17 14:29:14 by julrusse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= so_long.a
TARGET	= so_long
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx
MLX = $(MLX_DIR)/libmlx.a

INCLUDES = -I includes -I $(LIBFT_DIR) -I $(MLX_DIR)

SRC =	read_map.c \
		utils.c \
		validate_map.c \
		validate_path.c \
		validate_utils.c \
		validate_walls.c \
		render.c \
		game.c \
		main.c

OBJ_DIR = obj
OBJ		= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(TARGET)

$(LIBFT):
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@echo "Compiling MiniLibX..."
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ)
	@echo "Creating $(NAME)..."
	@ar rcs $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET): $(LIBFT) $(MLX) $(NAME)
	@echo "Building final executable $(TARGET)..."
	@$(CC) $(CFLAGS) -o $(TARGET) main.c $(NAME) -Llibft -lft -Lminilibx -lmlx -lm -lXext -lX11

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Nettoyage des objets du projet
clean:
	@echo "Cleaning objects..."
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean

# Nettoyage complet
fclean: clean
	@echo "Cleaning everything..."
	@rm -f $(NAME) $(TARGET)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) clean

# Recompile tout
re: fclean all

.PHONY: all clean fclean re
