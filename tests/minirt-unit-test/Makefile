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
SRC_DIR_PLANES := tests_planes
SRC_DIR_CUB_CYL := tests_cub_cyl
SRC_DIR_CONES := tests_cones
SRC_DIR_TRIANGLES := tests_triangles
SRC_DIR_GROUPS := tests_groups
SRC_DIR_PATTERNS := tests_patterns
SRC_DIR_TEXTURES := tests_textures
SRC_DIR_OBJ_FILES := tests_obj_files
SRC_DIR_REFLECT := tests_reflection
SRC_DIR_REFRACT := tests_refraction

SRCS := \
	main.c \
	$(SRC_DIR_PLANES)/00_test_planes_launcher.c \
	$(SRC_DIR_PLANES)/01_test_plane.c \
	$(SRC_DIR_SHAPES)/00_test_shapes_launcher.c \
	$(SRC_DIR_SHAPES)/01_test_shape.c \
	$(SRC_DIR_SHAPES)/02_test_shape_transform.c \
	$(SRC_DIR_SHAPES)/03_test_shape_material.c \
	$(SRC_DIR_SHAPES)/04_test_shape_ass_material.c \
	$(SRC_DIR_SHAPES)/05_test_shape_intersect.c \
	$(SRC_DIR_SHAPES)/06_test_shape_translate.c \
	$(SRC_DIR_SHAPES)/07_test_shape_normal_translate.c \
	$(SRC_DIR_SHAPES)/08_test_shape_normal_transform.c \
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
	$(SRC_DIR_PATTERNS)/00_test_patterns_launcher.c \
	$(SRC_DIR_PATTERNS)/01_test_pattern.c \
	$(SRC_DIR_PATTERNS)/02_test_pattern_stripe_y.c \
	$(SRC_DIR_PATTERNS)/03_test_pattern_stripe_z.c \
	$(SRC_DIR_PATTERNS)/04_test_pattern_stripe_x.c \
	$(SRC_DIR_PATTERNS)/05_test_pattern_lighting.c \
	$(SRC_DIR_PATTERNS)/06_test_pattern_obj_transform.c \
	$(SRC_DIR_PATTERNS)/07_test_pattern_pat_transform.c \
	$(SRC_DIR_PATTERNS)/08_test_pattern_all_transform.c \
	$(SRC_DIR_PATTERNS)/09_test_pattern.c \
	$(SRC_DIR_PATTERNS)/10_test_pattern_set_transform.c \
	$(SRC_DIR_PATTERNS)/11_test_pattern_uv_checkers.c \
	$(SRC_DIR_PATTERNS)/12_test_pattern_spherical_map.c \
	$(SRC_DIR_PATTERNS)/13_test_pattern_align_check.c \
	$(SRC_DIR_PATTERNS)/14_test_pattern_identify_cube_face.c \
	$(SRC_DIR_PATTERNS)/15_test_pattern_colors_mapped_cube.c \
	$(SRC_DIR_TEXTURES)/00_test_textures_launcher.c \
	$(SRC_DIR_TEXTURES)/01_test_textures_wrong_header.c \
	$(SRC_DIR_TEXTURES)/02_test_textures_size.c \
	$(SRC_DIR_TEXTURES)/03_test_textures_read_pixel.c \
	$(SRC_DIR_TEXTURES)/04_test_textures_comments.c \
	$(SRC_DIR_TEXTURES)/05_test_textures_rgb_span.c \
	$(SRC_DIR_TEXTURES)/06_test_textures_rgb_scaling.c \
	$(SRC_DIR_TEXTURES)/07_test_textures_2D_checkers.c \
	$(SRC_DIR_OBJ_FILES)/00_test_obj_files_launcher.c \
	$(SRC_DIR_OBJ_FILES)/01_test_obj_files_gibberish.c \
	$(SRC_DIR_OBJ_FILES)/02_test_obj_files_vertices.c \
	$(SRC_DIR_OBJ_FILES)/03_test_obj_files_faces.c \
	$(SRC_DIR_REFLECT)/00_test_reflect_launcher.c \
	$(SRC_DIR_REFLECT)/01_test_reflective.c \
	$(SRC_DIR_REFLECT)/02_test_reflect_comps.c \
	$(SRC_DIR_REFLECT)/03_test_reflect_col_nonreflect.c \
	$(SRC_DIR_REFLECT)/04_test_reflect_col_reflective.c \
	$(SRC_DIR_REFLECT)/05_test_reflect_shade_hit_reflective.c \
	$(SRC_DIR_REFLECT)/06_test_reflect_mutually_reflective.c \
	$(SRC_DIR_REFLECT)/07_test_reflect_col_max_recursion.c \
	$(SRC_DIR_REFRACT)/00_test_refract_launcher.c \
	$(SRC_DIR_REFRACT)/01_test_refract_and_transp.c \
	$(SRC_DIR_REFRACT)/02_test_refract_glass_sphere.c \
	$(SRC_DIR_REFRACT)/03_test_refract_find_n1_n2.c \
	$(SRC_DIR_REFRACT)/04_test_refract_under_point.c \
	$(SRC_DIR_REFRACT)/05_test_refract_color_opaque.c \
	$(SRC_DIR_REFRACT)/06_test_refract_max_recursion.c \
	$(SRC_DIR_REFRACT)/07_test_refract_total.c \
	$(SRC_DIR_REFRACT)/08_test_refract_color.c \
	$(SRC_DIR_REFRACT)/09_test_refract_shade_hit.c \
	$(SRC_DIR_REFRACT)/10_schlick_total.c \
	$(SRC_DIR_REFRACT)/11_schlick_perpendicular.c \
	$(SRC_DIR_REFRACT)/12_schlick_n2_bigger_n1.c \
	$(SRC_DIR_REFRACT)/13_shadehit_reflective_and_transparent.c \
	$(SRC_DIR_CUB_CYL)/00_test_cubes_launcher.c \
	$(SRC_DIR_CUB_CYL)/01_test_cubes_intersect.c \
	$(SRC_DIR_CUB_CYL)/02_test_cubes_ray_misses.c \
	$(SRC_DIR_CUB_CYL)/03_test_cubes_normal_at.c \
	$(SRC_DIR_CUB_CYL)/04_test_cyls_ray_misses.c \
	$(SRC_DIR_CUB_CYL)/05_test_cyls_ray_strikes.c \
	$(SRC_DIR_CUB_CYL)/06_test_cyls_local_normal.c \
	$(SRC_DIR_CUB_CYL)/07_test_cyls_min_max.c \
	$(SRC_DIR_CUB_CYL)/08_test_cyls_intersect_constrained.c \
	$(SRC_DIR_CUB_CYL)/09_test_cyls_intersecting_caps.c \
	$(SRC_DIR_CUB_CYL)/10_test_cyls_normal_caps.c \
	$(SRC_DIR_CONES)/00_test_cones_launcher.c \
	$(SRC_DIR_CONES)/01_test_cones_intersect.c \
	$(SRC_DIR_CONES)/02_test_cones_intersect_parallel.c \
	$(SRC_DIR_CONES)/03_test_cones_intersect_caps.c \
	$(SRC_DIR_TRIANGLES)/00_test_triangles_launcher.c \
	$(SRC_DIR_TRIANGLES)/01_test_triangles_create.c \
	$(SRC_DIR_TRIANGLES)/02_test_triangles_normal_at.c \
	$(SRC_DIR_TRIANGLES)/03_test_triangles_ray_parallel.c \
	$(SRC_DIR_TRIANGLES)/04_test_triangles_ray_misses_p1-p3.c \
	$(SRC_DIR_TRIANGLES)/05_test_triangles_ray_misses_p1-p2-p3.c \
	$(SRC_DIR_TRIANGLES)/06_test_triangles_ray_strikes.c \
	$(SRC_DIR_GROUPS)/00_test_groups_launcher.c \
	$(SRC_DIR_GROUPS)/01_test_groups_basic.c \
	$(SRC_DIR_GROUPS)/02_test_groups_has_parent.c \
	$(SRC_DIR_GROUPS)/03_test_groups_add_child.c \
	$(SRC_DIR_GROUPS)/04_test_groups_intersect_empty.c \
	$(SRC_DIR_GROUPS)/05_test_groups_intersect.c \
	$(SRC_DIR_GROUPS)/06_test_groups_intersect_transformed.c \
	$(SRC_DIR_GROUPS)/07_test_groups_point_convert_space.c \
	$(SRC_DIR_GROUPS)/08_test_groups_normal_convert_space.c \
	$(SRC_DIR_GROUPS)/09_test_groups_object_normal.c \
    $(PRG_DIR)/src/file_helpers.c \
    $(PRG_DIR)/src/parsing_1.c \
    $(PRG_DIR)/src/parsing_tokens.c \
    $(PRG_DIR)/src/parsing_world.c \
    $(PRG_DIR)/src/parsing_ambient.c \
    $(PRG_DIR)/src/parsing_camera.c \
    $(PRG_DIR)/src/parsing_light.c \
    $(PRG_DIR)/src/parsing_light_bonus.c \
    $(PRG_DIR)/src/parsing_plane.c \
    $(PRG_DIR)/src/parsing_sphere.c \
    $(PRG_DIR)/src/parsing_cyl.c \
    $(PRG_DIR)/src/parsing_cyl_2.c \
    $(PRG_DIR)/src/parsing_cube.c \
    $(PRG_DIR)/src/parsing_cube_2.c \
    $(PRG_DIR)/src/parsing_cone.c \
    $(PRG_DIR)/src/parsing_cone_2.c \
    $(PRG_DIR)/src/parsing_checklist.c \
    $(PRG_DIR)/src/parsing_atof.c \
    $(PRG_DIR)/src/parsing_atorgb.c \
    $(PRG_DIR)/src/parsing_atof_tuple.c \
    $(PRG_DIR)/src/parsing_utils.c \
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
    $(PRG_DIR)/src/export_ppm.c \
    $(PRG_DIR)/src/patterns.c \
    $(PRG_DIR)/src/pat_checkers.c \
    $(PRG_DIR)/src/pat_gradient.c \
    $(PRG_DIR)/src/pat_ring.c \
    $(PRG_DIR)/src/pat_stripe.c \
    $(PRG_DIR)/src/pat_texture_map.c \
    $(PRG_DIR)/src/pat_uv_checkers.c \
    $(PRG_DIR)/src/pat_uv_image.c \
    $(PRG_DIR)/src/pat_uv_maps.c \
    $(PRG_DIR)/src/pat_uv_align_check.c \
    $(PRG_DIR)/src/pat_tests.c \
    $(PRG_DIR)/src/reflection.c \
    $(PRG_DIR)/src/groups.c \
    $(PRG_DIR)/src/uv_mapping.c \
    $(PRG_DIR)/src/textures.c \
    $(PRG_DIR)/src/sh_cone.c \
    $(PRG_DIR)/src/sh_cube.c \
    $(PRG_DIR)/src/sh_cylinder.c \
    $(PRG_DIR)/src/sh_group.c \
    $(PRG_DIR)/src/sh_plane.c \
    $(PRG_DIR)/src/sh_sphere.c \
    $(PRG_DIR)/src/sh_triangle.c \
    $(PRG_DIR)/src/sh_hexagon.c \
    $(PRG_DIR)/src/sh_test_shapes.c \
    $(PRG_DIR)/src/obj_parser.c \
    $(PRG_DIR)/src/free.c \
    $(PRG_DIR)/src/world_scenes.c \
	$(PRG_DIR)/src/debug_prints.c \
	$(LIBFT_DIR)/ft_lstadd_back.c\
	$(LIBFT_DIR)/ft_lstadd_front.c\
	$(LIBFT_DIR)/ft_lstclear.c\
	$(LIBFT_DIR)/ft_lstdelone.c\
	$(LIBFT_DIR)/ft_lstiter.c\
	$(LIBFT_DIR)/ft_lstlast.c\
	$(LIBFT_DIR)/ft_lstmap.c\
	$(LIBFT_DIR)/ft_lstnew.c\
	$(LIBFT_DIR)/ft_lstsize.c


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

test: all
	./$(NAME)

re: fclean all

asan: CFLAGS  += -fsanitize=address -fsanitize=undefined -g
asan: LDLIBS += -fsanitize=address
asan: fclean all

gdb:  CFLAGS  += -g -O0 
gdb:  fclean all 


.PHONY: all clean fclean re
