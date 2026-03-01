
NAME = Cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJ_DIR = obj
MAN_DIR = mandatory
MLX_DIR = minilibx-linux
SRCS = main.c 
OBJS = $(SRCS:$(MAN_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)


$(NAME): $(OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) -Lminilibx-linux -lmlx_Linux -lX11 -lXext -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(MAN_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
