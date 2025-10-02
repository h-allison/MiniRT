# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/22 14:10:49 by hallison          #+#    #+#              #
#    Updated: 2025/10/02 14:07:12 by mmillhof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---- Project ----
NAME        := miniRT

SRC         := src/main.c \
               src/file_helpers.c \
               src/parsing_1.c \
               src/parsing_tokens.c \
               src/parsing_world.c \
               src/parsing_ambient.c \
               src/parsing_camera.c \
               src/parsing_light.c \
               src/parsing_light_bonus.c \
               src/parsing_plane.c \
               src/parsing_sphere.c \
               src/parsing_cyl.c \
               src/parsing_cyl_2.c \
               src/parsing_cube.c \
               src/parsing_cube_2.c \
               src/parsing_cone.c \
               src/parsing_cone_2.c \
               src/parsing_checklist.c \
               src/parsing_atof.c \
               src/parsing_atorgb.c \
               src/parsing_atof_tuple.c \
               src/parsing_utils.c \
               src/parsing_bonus_shapes.c \
               src/parsing_bonus_fields.c \
               src/error_handling.c \
               src/mlx_handling.c \
               src/mlx_keypress_1.c \
               src/mlx_keypress_2.c \
               src/mlx_keypress_3.c \
               src/rendering_1.c \
               src/rendering_2.c \
               src/rendering_3.c \
               src/rendering_4.c \
               src/math_float.c \
			   src/math_matrices_1.c \
			   src/math_matrices_2.c \
			   src/math_matrices_3.c \
			   src/math_matrices_4.c \
			   src/math_matrices_5.c \
               src/math_tuples_1.c \
               src/math_tuples_2.c \
               src/math_tuples_3.c \
			   src/math_transform.c \
			   src/math_transform_2.c \
			   src/math_rays.c \
			   src/math_intersections_1.c \
			   src/math_intersections_2.c \
			   src/math_intersections_3.c \
			   src/math_colors.c \
			   src/math_shading_1.c \
			   src/math_shading_2.c \
			   src/math_view.c \
			   src/create_objects.c \
               src/create_tuples.c \
			   src/create_matrices.c \
			   src/export_ppm.c \
			   src/patterns.c \
			   src/pat_checkers.c \
			   src/pat_gradient.c \
			   src/pat_ring.c \
			   src/pat_stripe.c \
			   src/pat_texture_map.c \
			   src/pat_uv_checkers.c \
			   src/pat_uv_image.c \
			   src/pat_uv_maps.c \
			   src/pat_tests.c \
			   src/reflection.c \
			   src/groups.c \
			   src/uv_mapping_1.c \
			   src/uv_mapping_2.c \
			   src/textures.c \
			   src/sh_cone_1.c \
			   src/sh_cone_2.c \
			   src/sh_cube.c \
			   src/sh_cylinder_1.c \
			   src/sh_cylinder_2.c \
			   src/sh_group.c \
			   src/sh_plane.c \
			   src/sh_sphere.c \
			   src/sh_triangle.c \
			   src/sh_hexagon.c \
			   src/sh_test_shapes.c \
			   src/obj_parser_1.c \
			   src/obj_parser_2.c \
			   src/free_1.c \
			   src/free_2.c \
			   src/world_scenes.c \
			   src/debug_prints.c

# ---- Paths ----
MLX42_PATH  := lib/MLX42
MLX42_A     := $(MLX42_PATH)/build/libmlx42.a

LIBFT_PATH  := lib/libft
LIBFT       := $(LIBFT_PATH)/libft.a

# ---- Toolchain ----
CC          ?= cc
CFLAGS      ?= -Wall -Wextra -Werror \
				-Iinclude -I$(MLX42_PATH)/include \
             	-I$(LIBFT_PATH)/include \
				-MMD -MP
LDFLAGS     := -L$(MLX42_PATH)/build -L$(LIBFT_PATH)
LDLIBS      := -lft -lmlx42 -lglfw -lm

# ---- OS-specific extras (GLFW deps) ----
UNAME_S     := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    LDLIBS  += -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo
else
    LDLIBS  += -ldl -lpthread
endif

# ---- Objects / Deps ----
OBJDIR      := build
OBJ         := $(patsubst src/%.c,$(OBJDIR)/%.o,$(SRC))
DEP         := $(OBJ:.o=.d)

# ---- Rules ----
.PHONY: all clean fclean re asan gdb valgrind valchild mlx42

all: $(NAME)

# Compile C -> .o into build/
$(OBJDIR)/%.o: src/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -O3 -c $< -o $@
	# $(CC) $(CFLAGS) -O0 -g -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build libft if needed
$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH) CFLAGS+=' -Iinclude'

# Build MLX42 if needed
mlx42: $(MLX42_A)

$(MLX42_A):
	@if [ ! -d "$(MLX42_PATH)" ]; then \
		echo "Cloning MLX42"; \
		git clone https://github.com/codam-coding-college/MLX42.git $(MLX42_PATH); \
	fi
	@if [ ! -f "$(MLX42_A)" ]; then \
		echo "Building MLX42"; \
		cmake -S $(MLX42_PATH) -B $(MLX42_PATH)/build -DMLX42_BUILD_EXAMPLES=OFF; \
		$(MAKE) -C $(MLX42_PATH)/build; \
	fi

# Build target
$(NAME): $(MLX42_A) $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -rf $(OBJDIR)
	@if [ -d "$(MLX42_PATH)/build" ]; then $(MAKE) -C $(MLX42_PATH)/build clean; fi

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(NAME)
	rm -rf $(MLX42_PATH)

re: fclean all

# ---- Debug/analysis profiles ----
asan: CFLAGS  += -fsanitize=address -fsanitize=undefined -g
asan: LDFLAGS += -fsanitize=address -fsanitize=undefined -g
asan: clean

gdb:  CFLAGS  += -g -O0
gdb:  fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --suppressions=valgrind-glibc-dlopen.supp --track-fds=yes ./$(NAME) samples/sample_0.rt

-include $(DEP)
