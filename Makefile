NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -I MLX42/include/MLX42 -I libft/include -fsanitize=address

OS = $(shell uname -s)

ifeq ($(OS),Darwin)
	# Make brew install in your HOME:
	# 	https://github.com/kube/42homebrew
	# brew install glfw
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
      mandatory/parse/parse_cub_file.c \
	  mandatory/parse/parse_map.c \
	  mandatory/parse/parse_textures_colors.c \
	  mandatory/parse/parse_utils.c \
	  mandatory/free_ressources/parse/parse_map.c


#SRC_BONUS = bonus/...

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(SRC)
	$(CC) $(CFLAGS) $(SRC) $(LFLAGS) -o $(NAME)

bonus: $(MLX) $(LIBFT) $(SRC_BONUS)
	$(CC) $(CFLAGS) $(SRC_BONUS) $(LFLAGS) -o $(NAME)

$(MLX):
	@mkdir -p MLX42/build
	@cd MLX42/build && cmake .. && make

$(LIBFT):
	make -C libft

clean:
	make -C libft clean
	make -C MLX42/build clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

restore: fclean
	rm -rf MLX42/build

.PHONY: all clean fclean re restore bonus