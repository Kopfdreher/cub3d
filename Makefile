# |--- Variables --------------------------------------------------------------|

NAME		= cub3d
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address

# Colors
GREEN		= \033[0;32m
BLUE		= \033[0;36m
RESET		= \033[0m

# Directories
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= includes

# Includes 
INC_FILES	= $(addsuffix .h, cub3d defines execute parse)
INCS		= $(addprefix $(INC_DIR)/, $(INC_FILES))

# Source files
ERROR_FILES	=
PARSE_FILES	=
EXEC_FILES	= init_session render_next_frame key_press_handler\
			  close_window_handler cast_rays
HELPER_FILES= helper_mlx
SRC_FILES	= $(addsuffix .c, main\
			  $(ERROR_FILES)\
			  $(PARSE_FILES)\
			  $(EXEC_FILES)\
			  $(HELPER_FILES))
SRCS		= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Object files
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Libft
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a

# Mlx
MLX_DIR		= ./minilibx-linux
MLX_LIB		= $(MLX_DIR)/libmlx_Linux.a

# Includes & Linking
INCLUDES	= -I. -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)
LDFLAGS		= -L$(LIBFT_DIR) -lft \
			  -L$(MLX_DIR) -lmlx_Linux \
			  -L/usr/lib -lXext -lX11 -lm -lz

# |--- Rules ------------------------------------------------------------------|

all: $(NAME)

# Main Traget
$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
		@echo "$(BLUE)|--Linking $(NAME)----------------|$(RESET)"
		@$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)
		@echo "$(GREEN)|--$(NAME) created successfully!--|$(RESET)"

# Libft
$(LIBFT):
		@echo "$(BLUE)|--Building Libft-------------------|$(RESET)"
		@make -C $(LIBFT_DIR) > /dev/null

# MLX
$(MLX_LIB):
		@echo "$(BLUE)|--Building MLX---------------------|$(RESET)"
		@make -C $(MLX_DIR) > /dev/null 2>&1

# Compiling .c to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INCS)
		@mkdir -p $(OBJ_DIR)
		@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# |--- CleanUp ----------------------------------------------------------------|

# Remove all Object-Files
clean:
		@echo "$(BLUE)|--Cleaning Objects-----------------|$(RESET)"
		@rm -rf $(OBJ_DIR)
		@make clean -C $(LIBFT_DIR) > /dev/null
		@make clean -C $(MLX_DIR) > /dev/null
		@echo "$(GREEN)|--Cleaned successfully!------------|$(RESET)"

# Remove all Object- and Archive-Files
fclean: clean
		@echo "$(BLUE)|--Cleaning Executables-------------|$(RESET)"
		@rm -f $(NAME) > /dev/null
		@echo "$(BLUE)|--Cleaning JSON-Files--------------|$(RESET)"
		@rm -f compile_commands.json
		@rm -rf .cache
		@make fclean -C $(LIBFT_DIR) > /dev/null
		@echo "$(GREEN)|--Cleaned successfully!------------|$(RESET)"

# Rebuild
re: fclean all

.PHONY: clean all re fclean
