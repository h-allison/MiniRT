# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/22 14:10:49 by hallison          #+#    #+#              #
#    Updated: 2025/09/22 20:38:30 by mmillhof         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ---- Project ----
NAME        := miniRT

SRC         := src/main.c \
               src/check_file.c \
               src/file_helpers.c \
               src/parsing_1.c \
               src/parsing_2.c \
               src/parsing_world.c \
               src/parsing_ambient.c \
               src/parsing_camera.c \
               src/parsing_light.c \
               src/parsing_bonus.c \
               src/parsing_atof.c \
               src/parsing_atorgb.c \
               src/parsing_atof_tuple.c \
               src/error_handling.c \
               src/mlx_handling.c \
               src/rendering.c \
               src/math_float.c \
			   src/math_matrices_1.c \
			   src/math_matrices_2.c \
			   src/math_matrices_3.c \
			   src/math_matrices_4.c \
               src/math_tuples_1.c \
               src/math_tuples_2.c \
               src/math_tuples_3.c \
			   src/math_transform.c \
			   src/math_transform_2.c \
			   src/math_rays.c \
			   src/math_intersections.c \
			   src/math_intersections_2.c \
			   src/math_colors.c \
			   src/math_shading.c \
			   src/math_shading_2.c \
			   src/math_view.c \
			   src/create_objects.c \
               src/create_tuples.c \
			   src/create_matrices.c \
			   src/export_ppm.c \
			   src/patterns.c \
			   src/reflection.c \
			   src/groups.c \
			   src/uv_mapping.c \
			   src/free.c \
			   src/world_scenes.c

# ---- Paths ----
LIBFT_PATH  := lib/libft
LIBFT       := $(LIBFT_PATH)/libft.a

MLX42_PATH  := lib/MLX42
MLX42_A     := $(MLX42_PATH)/build/libmlx42.a

# ---- Toolchain ----
CC          ?= cc
CFLAGS      ?= -Wall -Wextra -Werror
CPPFLAGS := -Iinclude \
             -I$(LIBFT_PATH)/include \
             -I$(MLX42_PATH)/include \
             -MMD -MP
LDFLAGS     := -L$(LIBFT_PATH) -L$(MLX42_PATH)/build
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
	$(CC) $(CFLAGS) $(CPPFLAGS) -O3 -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build libft if needed
$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH) CFLAGS+=' -Iinclude'

# Build MLX42 if needed
mlx42: $(MLX42_A)

$(MLX42_A):
	cmake -S $(MLX42_PATH) -B $(MLX42_PATH)/build -DMLX42_BUILD_EXAMPLES=OFF
	$(MAKE) -C $(MLX42_PATH)/build

# Build target
$(NAME): $(OBJ) $(LIBFT) $(MLX42_A)
	$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $@

clean:
	$(MAKE) -C $(LIBFT_PATH) clean
	rm -rf $(OBJDIR)
	@if [ -d "$(MLX42_PATH)/build" ]; then $(MAKE) -C $(MLX42_PATH)/build clean; fi

fclean: clean
	$(MAKE) -C $(LIBFT_PATH) fclean
	rm -f $(NAME)
	rm -rf $(MLX42_PATH)/build

re: fclean all

# ---- Debug/analysis profiles ----
asan: CFLAGS  += -fsanitize=address -fsanitize=undefined -g
asan: LDFLAGS += -fsanitize=address -fsanitize=undefined
asan: fclean all

gdb:  CFLAGS  += -g -O0
gdb:  fclean all

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes \
	         --track-fds=yes --quiet ./$(NAME)

valchild: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes \
	         --track-fds=yes --trace-children=yes --quiet ./$(NAME)

# Auto-include dependency files
-include $(DEP)
