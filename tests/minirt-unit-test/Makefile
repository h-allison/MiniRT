# Minimal Makefile

NAME := unit_test
CC   := cc

PRG_DIR        := ../..
FRAMEWORK_DIR  := ../libunit
LIBFT_DIR      := $(FRAMEWORK_DIR)/libft
MLX42_PATH     := $(PRG_DIR)/lib/MLX42
MLX42_A        := $(MLX42_PATH)/build/libmlx42.a

# Includes & warnings
CFLAGS  := -Wall -Wextra -Werror -g
CFLAGS  += -Iincludes -I$(PRG_DIR)/include -I$(FRAMEWORK_DIR)/includes -I$(LIBFT_DIR) -I$(MLX42_PATH)/include

# Link libs (use archive paths to avoid -L/-l for mlx42/libunit/libft)
LDLIBS := $(FRAMEWORK_DIR)/libunit.a $(LIBFT_DIR)/libft.a $(MLX42_A) -lglfw -lm

SRC_DIR := camera_tests

SRCS := \
	main.c \
	$(SRC_DIR)/00_camera_tests_launcher.c \
	$(SRC_DIR)/01_create_camera_test.c \
	$(PRG_DIR)/src/check_file.c \
	$(PRG_DIR)/src/file_helpers.c \
	$(PRG_DIR)/src/parsing.c \
	$(PRG_DIR)/src/error_handling.c \
	$(PRG_DIR)/src/mlx_handling.c \
	$(PRG_DIR)/src/rendering.c \
	$(PRG_DIR)/src/math_float.c \
	$(PRG_DIR)/src/math_matrices_1.c \
	$(PRG_DIR)/src/math_matrices_2.c \
	$(PRG_DIR)/src/math_matrices_3.c \
	$(PRG_DIR)/src/math_matrices_4.c \
	$(PRG_DIR)/src/math_tuples_1.c \
	$(PRG_DIR)/src/math_tuples_2.c \
	$(PRG_DIR)/src/math_tuples_3.c \
	$(PRG_DIR)/src/math_transform.c \
	$(PRG_DIR)/src/math_transform_2.c \
	$(PRG_DIR)/src/math_rays.c \
	$(PRG_DIR)/src/math_intersections.c \
	$(PRG_DIR)/src/math_intersections_2.c \
	$(PRG_DIR)/src/math_colors.c \
	$(PRG_DIR)/src/math_shading.c \
	$(PRG_DIR)/src/math_shading_2.c \
	$(PRG_DIR)/src/math_view.c \
	$(PRG_DIR)/src/create_objects.c \
	$(PRG_DIR)/src/create_tuples.c \
	$(PRG_DIR)/src/create_matrices.c \
	$(PRG_DIR)/src/export_ppm.c

OBJS := $(SRCS:.c=.o)

all: $(LIBFT_DIR)/libft.a $(FRAMEWORK_DIR)/libunit.a $(NAME)

$(NAME): $(OBJS) $(MLX42_A)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o $@

# Build local libraries via their own Makefiles
$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

$(FRAMEWORK_DIR)/libunit.a: $(LIBFT_DIR)/libft.a
	$(MAKE) -C $(FRAMEWORK_DIR)

clean:
	$(RM) $(OBJS)
	-$(MAKE) -C $(LIBFT_DIR) clean
	-$(MAKE) -C $(FRAMEWORK_DIR) clean

fclean: clean
	$(RM) $(NAME)
	-$(MAKE) -C $(FRAMEWORK_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

