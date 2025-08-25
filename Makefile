# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/18 22:29:32 by abendrih          #+#    #+#              #
#    Updated: 2025/08/25 07:18:43 by abendrih         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = fdf

# ┌─────────────────────────────┐
# │         REPERTOIRES         │
# └─────────────────────────────┘
SRC_DIR     = src
PARSING_DIR = parsing
INCLUDE_DIR = include
LIBFT_DIR   = libft
MLX_DIR     = minilibx-linux

LIBFT_LIB   = $(LIBFT_DIR)/libft.a
MLX_LIB     = $(MLX_DIR)/libmlx.a

# ┌─────────────────────────────┐
# │           SOURCES           │
# └─────────────────────────────┘
SRC         = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/fdf.c \
	$(PARSING_DIR)/parsing.c \
	$(PARSING_DIR)/parsing_utils.c \
	$(PARSING_DIR)/parsing_z.c \
	$(SRC_DIR)/graphics_init.c \
	$(SRC_DIR)/image.c \
	$(SRC_DIR)/hooks.c\


OBJ         = $(SRC:.c=.o)

# ┌─────────────────────────────┐
# │         COMPILATION         │
# └─────────────────────────────┘
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g3

# Linux link flags for MiniLibX
MLX_LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
MLX_CFLAGS  = -I$(MLX_DIR)

# ┌─────────────────────────────┐
# │           COULEURS          │
# └─────────────────────────────┘
RESET       = \033[0m
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RED         = \033[0;31m
CYAN        = \033[0;36m
MATRIX_GRAY = \033[38;5;246m
MATRIX_GREEN= \033[38;5;46m

MATRIX_CODE = "\n\
$(MATRIX_GREEN)\
> Initializing wireframe engine...\n\
> Injecting LIBFT Core [OK]\n\
> MiniLibX linked [OK]\n\
> Binary path secured: $(NAME)\n\
> Ready for rendering.\n\
> [▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓] 100%\n\
> SYSTEM READY.\n\
$(RESET)"

MATRIX_CLEAN = "\n\
\033[38;5;93m╔════════════════════════════════════╗\n\
\033[38;5;93m║ \033[38;5;51mPurging temporals...\033[0m               \033[38;5;93m║\n\
\033[38;5;93m║ \033[38;5;51m[▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓] \033[38;5;198m100%%\033[0m         \033[38;5;93m║\n\
\033[38;5;93m║ \033[38;5;201mAll objects neutralized\033[0m            \033[38;5;93m║\n\
\033[38;5;93m║ \033[38;5;51mFDF Renderer Offline\033[0m               \033[38;5;93m║\n\
\033[38;5;93m╚════════════════════════════════════╝\n\
$(RESET)"

# ┌─────────────────────────────┐
# │          COMMANDES          │
# └─────────────────────────────┘
all: $(NAME)

$(NAME): $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory 2>&1 | grep -v '^gcc'
	@echo "$(GREEN)Building MiniLibX...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory 1>/dev/null
	@echo "$(GREEN)Linking with LIBFT + MiniLibX...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT_LIB) $(MLX_LDFLAGS)
	@echo $(MATRIX_CODE)

%.o: %.c
	@echo "$(CYAN)Compiling$(RESET) $<"
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_DIR) $(MLX_CFLAGS) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	-@$(MAKE) -C $(MLX_DIR) clean --no-print-directory
	@echo "$(CYAN)Cleaning object files...$(RESET)"
	@rm -f $(OBJ)
	@echo $(MATRIX_CLEAN)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(RED)Removing binary:$(RESET) $(NAME)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
