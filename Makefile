NAME = fractol
NAME_BONUS = fractol_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror -O3

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a

LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
INCLUDES = -I. -I$(MLX_DIR)

# Main source files
SRCS = setup_mlx.c \
	   math_utils.c \
	   libft_stuff.c \
	   main.c \
	   drawing_fractal.c

# Bonus source files (complete separate set)
BONUS_SRCS = setup_mlx_bonus.c \
			 math_utils_bonus.c \
			 libft_stuff_bonus.c \
			 main_bonus.c \
			 drawing_fractal_bonus.c \
			 mouse_control_bonus.c

# Object files
OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(MLX_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(NAME_BONUS): $(MLX_LIB) $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBS) -o $(NAME_BONUS)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus