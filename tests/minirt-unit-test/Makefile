NAME := unit_test
CC   := cc

PRG_DIR        := ../..
FRAMEWORK_DIR  := ../libunit
LIBFT_DIR      := $(FRAMEWORK_DIR)/libft
MLX42_PATH     := $(PRG_DIR)/lib/MLX42
MLX42_BUILD    := $(MLX42_PATH)/build
MLX42_A        := $(MLX42_BUILD)/libmlx42.a

CFLAGS  := -Wall -Wextra -Werror -g
CFLAGS  += -Iincludes -I$(PRG_DIR)/include -I$(FRAMEWORK_DIR)/includes -I$(LIBFT_DIR) -I$(MLX42_PATH)/include

LDLIBS := $(FRAMEWORK_DIR)/libunit.a $(LIBFT_DIR)/libft.a $(MLX42_A) -lglfw -lm

SRC_DIR_CAMERA := tests_camera
SRC_DIR_SHADOW := tests_shadow
SRC_DIR_SHAPES := tests_shapes

SRCS := \
	main.c \
	$(SRC_DIR_SHAPES)/00_test_shapes_launcher.c \
	$(SRC_DIR_SHAPES)/01_test_shape.c \
	$(SRC_DIR_CAMERA)/00_test_camera_launcher.c \
	$(SRC_DIR_CAMERA)/01_test_camera_floats.c \
	$(SRC_DIR_CAMERA)/02_test_camera_idm.c \
	$(SRC_DIR_CAMERA)/03_test_camera_pixel.c \
	$(SRC_DIR_CAMERA)/04_test_camera_rayforpixel_1.c \
	$(SRC_DIR_CAMERA)/05_test_camera_rayforpixel_2.c \
	$(SRC_DIR_CAMERA)/06_test_camera_rayforpixel_3.c \
	$(SRC_DIR_SHADOW)/00_test_shadow_launcher.c \
	$(SRC_DIR_SHADOW)/01_test_shadow_in.c \
	$(SRC_DIR_SHADOW)/02_test_is_shad_1.c \
	$(SRC_DIR_SHADOW)/03_test_is_shad_2.c \
	$(SRC_DIR_SHADOW)/04_test_is_shad_3.c \
	$(SRC_DIR_SHADOW)/05_test_is_shad_4.c \
	$(SRC_DIR_SHADOW)/06_test_over_point.c \
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

$(MLX42_A):
	cmake -S $(MLX42_PATH) -B $(MLX42_BUILD)
	cmake --build $(MLX42_BUILD) -j

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

test: $(NAME)
	./$(NAME)

re: fclean all

.PHONY: all clean fclean re
