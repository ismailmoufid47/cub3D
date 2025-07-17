NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -I MLX42/include/MLX42 -I libft/include# -fsanitize=address

OS = $(shell uname -s)

ifeq ($(OS),Darwin)
	LFLAGS = -L MLX42/build -L $(HOME)/.brew/opt/glfw/lib -L libft -l mlx42 -l glfw -l ft \
			 -framework Cocoa -framework OpenGL -framework IOKit
else ifeq ($(OS),Linux)
	# sudo apt install -y libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev cmake build-essential
	LFLAGS = -L MLX42/build -L libft -l mlx42 -l glfw -l ft -l GL -l m -l pthread -l dl
else
	exit 1
endif

MLX = MLX42/build/libmlx42.a

LIBFT = libft/libft.a 

SRC = mandatory/cub3D.c \
      mandatory/parse/parse.c \
	  mandatory/parse/parse_map.c \
	  mandatory/parse/parse_textures.c \
	  mandatory/parse/utils/parse_utils.c \
	  mandatory/free_ressources/parse/parse_map.c

#SRC_BONUS = 

OBJ = $(SRC:%.c=obj/%.o)
#OBJ_BONUS = $(SRC_BONUS:%.c=obj/%.o)


$(NAME): $(MLX) $(LIBFT) $(OBJ) mandatory/include/cub3D.h
	$(CC) $(OBJ) $(LFLAGS) -o $(NAME)

$(MLX):
	@mkdir -p MLX42/build
	@cd MLX42/build && cmake .. && make

$(LIBFT):
	make -C libft

obj/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


all: $(NAME)

bonus: $(MLX) $(LIBFT) $(OBJ_BONUS)
	$(CC) $(OBJ_BONUS) $(LFLAGS) -o $(NAME)

clean:
	make -C libft clean
	make -C MLX42/build clean
	rm -rf obj

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

restore: fclean
	rm -rf MLX42/build

.PHONY: all clean fclean re restore bonus