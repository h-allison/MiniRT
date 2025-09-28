/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_scenes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 18:12:31 by hallison          #+#    #+#             */
/*   Updated: 2025/09/24 16:22:49 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

t_world	default_world(void)
{
	t_world	w;
	t_shape	*s1;
	t_shape	*s2;
	t_light	*light;

	light = point_light(point(-10, 10, -10), color(255, 255, 255));
	s1 = sphere();
	s1->m->color = color(204, 255, 153);
	s1->m->diffuse = 0.7;
	s1->m->specular = 0.2;
	s2 = sphere();
	set_transform(s2, scaling(0.5, 0.5, 0.5));
	w.s = ft_calloc(5, sizeof(t_shape *));
	w.s[0] = s1;
	w.s[1] = s2;
	w.light = ft_calloc(2, sizeof(t_light *));
	if (!w.light)
		exit (1);
	w.light[0] = light;
	return (w);
}

t_world	default_world_rotation(void)
{
	t_world	w;
	t_shape	*s1;
	t_shape	*s2;
	t_light	*light;

	light = point_light(point(-10, 10, -10), color(255, 255, 255));
	s1 = sphere();
	s1->m->color = color(255, 0, 0);
//	s1->m->diffuse = 0.7;
//*	s1->m->specular = 0.2;
	s2 = sphere();
	s2->m->color = color(0, 255, 0);
	w.s = ft_calloc(5, sizeof(t_shape *));
	w.s[0] = s1;
	w.s[1] = s2;
	w.light = ft_calloc(2, sizeof(t_light *));
	if (!w.light)
		exit (1);
	w.light[0] = light;
	s1->transform = mmultfree(rotation_x(90 * DEG2RAD), s1->transform);
	free_matrix(s1->invtrans, 4);
	s2->invtrans = minvert(s1->transform, 4);
	s2->transform = mmultfree(rotation_x(90 * DEG2RAD), s2->transform);
	free_matrix(s2->invtrans, 4);
	s2->invtrans = minvert(s2->transform, 4);
	return (w);
}

t_world	default_world_2(void)
{
	t_world	w;
	t_shape	*floor;
	t_shape	*left_wall;
	t_shape	*right_wall;
	t_shape	*middle;
	t_shape	*right;
	t_shape	*left;

	floor = sphere();
	floor->transform = mmultfree(scaling(10, 0.01, 10), floor->transform);
	floor->invtrans = minvert(floor->transform, 4);
	floor->m->color = color(255, 230, 230);
	floor->m->specular = 0;

	left_wall = sphere();
	left_wall->transform = mmultfree(scaling(10, 0.01, 10), left_wall->transform);
	left_wall->transform = mmultfree(rotation_x(M_PI / 2), left_wall->transform);
	left_wall->transform = mmultfree(rotation_y(-M_PI / 4), left_wall->transform);
	left_wall->transform = mmultfree(translation(0, 0, 5), left_wall->transform);
	left_wall->invtrans = minvert(left_wall->transform, 4);
	left_wall->m = floor->m;

	right_wall = sphere();
	right_wall->transform = mmultfree(scaling(10, 0.01, 10), right_wall->transform);
	right_wall->transform = mmultfree(rotation_x(M_PI / 2), right_wall->transform);
	right_wall->transform = mmultfree(rotation_y(M_PI / 4), right_wall->transform);
	right_wall->transform = mmultfree(translation(0, 0, 5), right_wall->transform);
	right_wall->invtrans = minvert(right_wall->transform, 4);
	right_wall->m = floor->m;

	middle = sphere();
	middle->transform = mmultfree(translation(-0.5, 1, 0.5), middle->transform);
	middle->invtrans = minvert(middle->transform, 4);
	middle->m->color = color(26, 255, 128);
	middle->m->diffuse = 0.7;
	middle->m->specular = 0.3;

	right = sphere();
	right->transform = mmultfree(scaling(0.5, 0.5, 0.5), right->transform);
	right->transform = mmultfree(translation(1.5, 0.5, -0.5), right->transform);
	right->invtrans = minvert(right->transform, 4);
	right->m->color = color(128, 255, 26);
	right->m->diffuse = 0.7;
	right->m->specular = 0.3;

	left = sphere();
	left->transform = mmultfree(scaling(0.33, 0.33, 0.33), left->transform);
	left->transform = mmultfree(translation(-1.5, 0.33, -0.75), left->transform);
	left->invtrans = minvert(left->transform, 4);
	left->m->color = color(255, 204, 26);
	left->m->diffuse = 0.7;
	left->m->specular = 0.3;

	w.light = ft_calloc(2, sizeof(t_light *));
	if (!w.light)
		exit (1);
	w.light[0] = point_light(point(-10, 10, -10), color(255, 255, 255));

	w.s = ft_calloc(7, sizeof(t_shape *));
	w.s[0] = floor;
	w.s[1] = left_wall;
	w.s[2] = right_wall;
	w.s[3] = middle;
	w.s[4] = right;
	w.s[5] = left;
	return (w);
}

t_world	default_world_3(void)
{
	t_world	w;
	t_shape	*floor;
	t_shape	*middle;
	t_shape	*right;
	t_shape	*left;

	floor = plane();
	floor->invtrans = minvert(floor->transform, 4);
	floor->m->color = color(255, 230, 230);
	floor->m->diffuse = .4;
	floor->m->ambient = 0;
	floor->m->specular = 0;
	floor->m->pattern = stripe_pattern(color(160, 130, 130), floor->m->color);

	middle = sphere();
	middle->transform = mmultfree(translation(-0.5, 1, 0.5), middle->transform);
	middle->invtrans = minvert(middle->transform, 4);
	middle->m->color = color(26, 150, 200);
	middle->m->diffuse = 0.7;
	middle->m->specular = 0.3;

	right = sphere();
	right->transform = mmultfree(scaling(0.5, 0.5, 0.5), right->transform);
	right->transform = mmultfree(translation(1.5, 0.5, -0.5), right->transform);
	right->invtrans = minvert(right->transform, 4);
	right->m->color = color(128, 255, 26);
	right->m->diffuse = 0.7;
	right->m->specular = 0.3;

	left = sphere();
	left->transform = mmultfree(scaling(0.33, 0.33, 0.33), left->transform);
	left->transform = mmultfree(translation(-1.5, 0.33, -0.75), left->transform);
	left->invtrans = minvert(left->transform, 4);
	left->m->color = color(255, 204, 26);
	left->m->diffuse = 0.7;
	left->m->specular = 0.3;

	w.light = ft_calloc(2, sizeof(t_light *));
	if (!w.light)
		exit (1);
	w.light[0] = point_light(point(-10, 10, -10), color(255, 255, 255));

	w.s = ft_calloc(5, sizeof(t_shape *));
	w.s[0] = floor;
	w.s[1] = middle;
	w.s[2] = right;
	w.s[3] = left;
	return (w);
}

t_world	default_world_4(void)
{
	t_world	w;
	t_shape	*floor;
	t_shape	*wall_back;
	t_shape	*middle;
	t_shape	*right;
	t_shape	*left;
	
	floor = plane();
	floor->invtrans = minvert(floor->transform, 4);
	floor->m->color = color(200, 200, 200);
	floor->m->diffuse = 0.7;
	floor->m->ambient = 0.0;
	floor->m->specular = 0.1;
	floor->m->reflective = 0.1;
	floor->m->pattern = checkers_pattern(color(100, 80, 60), floor->m->color);

	wall_back = plane();
	wall_back->transform = mmultfree(rotation_x(M_PI / 2), wall_back->transform);
	wall_back->transform = mmultfree(translation(0, 0, 40), wall_back->transform);
	wall_back->invtrans = minvert(wall_back->transform, 4);
	wall_back->m->color = color(80, 0, 0);
	wall_back->m->diffuse = 0.5;
	wall_back->m->ambient = 0;
	wall_back->m->specular = 0;
	wall_back->m->pattern = gradient_pattern(wall_back->m->color, color(0, 0, 180)) ; 
	wall_back->m->pattern->transform = mmultfree(scaling(18, 1, 1), wall_back->m->pattern->transform);
	wall_back->m->pattern->transform = mmultfree(rotation_y(90 * DEG2RAD), wall_back->m->pattern->transform);
	wall_back->m->pattern->invtrans = minvert(wall_back->m->pattern->transform, 4);

	left = sphere();
	left->transform = mmultfree(scaling(0.33, 0.33, 0.33), left->transform);
	left->transform = mmultfree(translation(-1.5, 0.33, -0.75), left->transform);
	left->invtrans = minvert(left->transform, 4);
	left->m->color = color(255, 128, 128);
	left->m->diffuse = 0.7;
	left->m->specular = 0.5;

	middle = sphere();
	middle->transform = mmultfree(translation(-0.5, 1, 1.5), middle->transform);
	middle->invtrans = minvert(middle->transform, 4);
	middle->m->color = color(10, 10, 10);
	middle->m->diffuse = 1;
	middle->m->specular = 0.1;
	middle->m->reflective = 1;

	right = sphere();
	right->transform = mmultfree(scaling(0.5, 0.5, 0.5), right->transform);
	right->transform = mmultfree(translation(1.5, 0.5, -0.5), right->transform);
	right->invtrans = minvert(right->transform, 4);
	right->m->color = color(140, 100, 255);
	right->m->diffuse = 0.7;
	right->m->specular = 0.4;
	right->m->pattern = ring_pattern(color(20, 80, 60), right->m->color);
	right->m->pattern->transform = mmultfree(scaling(0.1, 0.2, 0.2), right->m->pattern->transform);
	right->m->pattern->invtrans = minvert(right->m->pattern->transform, 4);
	
	w.light = ft_calloc(4, sizeof(t_light *));
	if (!w.light)
		exit (1);
	w.light[0] = point_light(point(-7, 7, -6), color(160, 40, 40));
	w.light[0]->last = false;
	w.light[1] = point_light(point(7, 7, -6), color(40, 40, 160));
	w.light[1]->last = false;
	w.light[2] = point_light(point(-2, 3, -6), color(40, 160, 40));

	w.s = ft_calloc(6, sizeof(t_shape *));
	w.s[0] = floor;
	w.s[1] = wall_back;
	w.s[2] = middle;
	w.s[3] = right;
	w.s[4] = left;
	return (w);
}

t_world	default_world_5(void)
{
	t_world	w;
	t_shape	*floor;
	t_shape	*big;
	t_shape	*middle;
	t_shape	*right;
	t_shape	*left;
	
	floor = plane();
	floor->invtrans = minvert(floor->transform, 4);
	floor->m->color = color(200, 200, 200);
	floor->m->diffuse = 0.7;
	floor->m->ambient = 0.01;
	floor->m->specular = 0.1;
	floor->m->reflective = .1;
	floor->m->pattern = ring_pattern(color(80, 80, 80), floor->m->color);

	big = plane();
	big->transform = mmultfree(translation(0, 8, 8), big->transform);
	big->transform = mmultfree(rotation_x(80 * DEG2RAD), big->transform);
	big->transform = mmultfree(rotation_y(20 * DEG2RAD), big->transform);
	big->invtrans = minvert(big->transform, 4);
	big->m->color = color(220, 230, 255);
	big->m->diffuse = .1;
	big->m->ambient = 0;
	big->m->specular = 0;
	big->m->reflective = 0.7;

	left = sphere();
	left->transform = mmultfree(scaling(0.33, 0.33, 0.33), left->transform);
	left->transform = mmultfree(translation(-2, 0.33, 0), left->transform);
	left->invtrans = minvert(left->transform, 4);
	left->m->color = color(255, 128, 128);
	left->m->diffuse = 0.7;
	left->m->specular = 0.5;

	middle = sphere();
	middle->transform = mmultfree(translation(-0.2, 1, 1), middle->transform);
	middle->invtrans = minvert(middle->transform, 4);
	middle->m->color = color(138, 132, 70);
	middle->m->diffuse = 0.1;
	middle->m->specular = 0.2;
	middle->m->reflective = 0.8;

	right = sphere();
	right->transform = mmultfree(scaling(0.5, 0.5, 0.5), right->transform);
	right->transform = mmultfree(translation(1.5, 0.5, -1), right->transform);
	right->invtrans = minvert(right->transform, 4);
	right->m->color = color(140, 100, 255);
	right->m->diffuse = 0.7;
	right->m->specular = 0.4;
	right->m->pattern = ring_pattern(color(20, 80, 60), right->m->color);
	right->m->pattern->transform = mmultfree(scaling(0.1, 0.2, 0.2), right->m->pattern->transform);
	right->m->pattern->invtrans = minvert(right->m->pattern->transform, 4);
	
	w.light = ft_calloc(2, sizeof(t_light *));
	if (!w.light)
		exit (1);
	w.light[0] = point_light(point(-7, 7, -6), color(255, 255, 240));

	w.s = ft_calloc(8, sizeof(t_shape *));
	w.s[0] = floor;
	w.s[1] = big;
	w.s[2] = middle;
	w.s[3] = right;
	w.s[4] = left;
	return (w);
}

t_world	default_world_6(void)
{
	t_world	w;
	t_shape	*floor;
	t_shape	*big;
	t_shape	*middle;
	t_shape	*right;
	t_shape	*left;
	t_shape *cub;
	
	floor = plane();
	floor->invtrans = minvert(floor->transform, 4);
	floor->m->color = color(200, 200, 200);
	floor->m->diffuse = 0.7;
	floor->m->ambient = 0.01;
	floor->m->specular = 0.2;
	floor->m->reflective = .2;
	floor->m->pattern = ring_pattern(color(80, 80, 80), floor->m->color);

	big = sphere();
	big->transform = mmultfree(translation(.5, 1, 4), big->transform);
	big->invtrans = minvert(big->transform, 4);
	big->m->color = color(140, 130, 100);
	big->m->diffuse = .6;
	big->m->ambient = .2;
	big->m->specular = 0.5;
	big->m->pattern = stripe_pattern(color(80, 80, 80), big->m->color);
	big->m->pattern->transform = mmultfree(scaling(0.4, 0.4, 0.6), big->m->pattern->transform);
	big->m->pattern->invtrans = minvert(big->m->pattern->transform, 4);

	left = sphere();
	left->transform = mmultfree(scaling(0.33, 0.33, 0.33), left->transform);
	left->transform = mmultfree(translation(-2, 0.33, 2), left->transform);
	left->invtrans = minvert(left->transform, 4);
	left->m->color = color(128, 120, 70);
	left->m->diffuse = 0.4;
	left->m->specular = 0.1;
	left->m->ambient = 0.1;
	left->m->reflective = 0.7;
	left->m->transparency = 0;

	middle = sphere();
	middle->transform = mmultfree(translation(-0.2, 1, -2), middle->transform);
	middle->invtrans = minvert(middle->transform, 4);
	middle->m->color = color(10, 20, 15);
	middle->m->diffuse = 1;
	middle->m->specular = 1;
	middle->m->shininess = 300;
	middle->m->ambient = 0.1;
	middle->m->reflective = 2;
	middle->m->transparency = 0.9;
	middle->m->refractive_index = 1.5;

	right = sphere();
	right->transform = mmultfree(scaling(0.5, 0.5, 0.5), right->transform);
	right->transform = mmultfree(translation(4, 0.5, 2.5), right->transform);
	right->invtrans = minvert(right->transform, 4);
	right->m->color = color(140, 100, 255);
	right->m->diffuse = 0.7;
	right->m->specular = 0.4;
	right->m->pattern = ring_pattern(color(20, 80, 60), right->m->color);
	right->m->pattern->transform = mmultfree(scaling(0.1, 0.2, 0.2), right->m->pattern->transform);
	right->m->pattern->invtrans = minvert(right->m->pattern->transform, 4);
	
	cub = cube();
	cub->transform = mmultfree(rotation_y(30 * DEG2RAD), cub->transform);
	cub->transform = mmultfree(scaling(0.2, 0.2, 0.2), cub->transform);
	cub->transform = mmultfree(translation(-1.8, 0.2, -1), cub->transform);
	cub->invtrans = minvert(cub->transform, 4);
	cub->m->color = color(40, 70, 100);
	cub->m->diffuse = .6;
	cub->m->ambient = .3;
	cub->m->specular = 0.6;
	cub->m->reflective = 0.4;

	w.light = ft_calloc(2, sizeof(t_light *));
	if (!w.light)
		exit (1);
	w.light[0] = point_light(point(-7, 7, -6), color(255, 255, 240));

	w.s = ft_calloc(8, sizeof(t_shape *));
	w.s[0] = floor;
	w.s[1] = big;
	w.s[2] = middle;
	w.s[3] = right;
	w.s[4] = left;
	w.s[5] = cub;
	return (w);
}

t_world	default_world_cyl(void)
{
	t_world	w;
	t_shape	*floor;
	t_shape	*big;
	t_shape	*middle;
	t_shape	*right;
	t_shape	*left;
	t_shape *cub;
	t_shape	*hex;
	
	floor = plane();
	floor->invtrans = minvert(floor->transform, 4);
	floor->m->color = color(200, 200, 200);
	floor->m->diffuse = 0.7;
	floor->m->ambient = 0.01;
	floor->m->specular = 0.2;
	floor->m->reflective = .2;
	floor->m->pattern = ring_pattern(color(80, 80, 80), floor->m->color);

	big = sphere();
	big->transform = mmultfree(translation(.5, 1, 4), big->transform);
	big->invtrans = minvert(big->transform, 4);
	big->m->color = color(140, 130, 100);
	big->m->diffuse = .6;
	big->m->ambient = .2;
	big->m->specular = 0.5;
	big->m->pattern = texture_map(uv_image(canvas_from_ppm("samples/textures/earthmap1k.ppm")), spherical_map);

	left = cylinder();
	left->minimum = 0;
	left->maximum = 2;
	left->closed = true;
	left->transform = mmultfree(scaling(0.5, 0.5, 0.5), left->transform);
	left->transform = mmultfree(translation(-2.5, 0.3, 2), left->transform);
	left->invtrans = minvert(left->transform, 4);
	left->m->color = color(20, 0, 10);
	left->m->diffuse = 1;
	left->m->specular = 1;
	left->m->ambient = 0.1;
	left->m->reflective = 2;
	left->m->transparency = 1;
	left->m->refractive_index = 1.5;

	middle = sphere();
	middle->transform = mmultfree(translation(-0.2, 1, -2), middle->transform);
	middle->invtrans = minvert(middle->transform, 4);
	middle->m->color = color(10, 20, 15);
	middle->m->diffuse = 1;
	middle->m->specular = 1;
	middle->m->shininess = 300;
	middle->m->ambient = 0.1;
	middle->m->reflective = 2;
	middle->m->transparency = 0.9;
	middle->m->refractive_index = 1.5;

	right = cone();
	right->minimum = -1;
	right->maximum = 1;
	right->closed = true;
	right->transform = mmultfree(rotation_z(90 * DEG2RAD), right->transform);
	right->transform = mmultfree(rotation_y(75 * DEG2RAD), right->transform);
	right->transform = mmultfree(scaling(1, 1, 1), right->transform);
	right->transform = mmultfree(translation(6, 1, 3), right->transform);
	right->invtrans = minvert(right->transform, 4);
	right->m->color = color(220, 220, 220);
	right->m->ambient = 0.3;
	right->m->diffuse = 0.5;
	right->m->specular = 2;
	right->m->reflective = 0;
	right->m->pattern = stripe_pattern(color(100, 60, 100), right->m->color);
	right->m->pattern->transform = mmultfree(rotation_z(-90 * DEG2RAD), right->m->pattern->transform);
	right->m->pattern->transform = mmultfree(scaling(.15, .15, .15), right->m->pattern->transform);
	right->m->pattern->invtrans = minvert(right->m->pattern->transform, 4);
	
	cub = cube();
	cub->transform = mmultfree(rotation_y(30 * DEG2RAD), cub->transform);
	cub->transform = mmultfree(scaling(0.33, 0.33, 0.33), cub->transform);
	cub->transform = mmultfree(translation(-1.8, 0.33, -1), cub->transform);
	cub->invtrans = minvert(cub->transform, 4);
	cub->m->color = color(0, 50, 100);
	cub->m->diffuse = .9;
	cub->m->ambient = .6;
	cub->m->specular = 0.6;
	cub->m->reflective = 0.1;
	cub->m->pattern = texture_map(uv_checkers(4, 4, color(70, 100, 0), cub->m->color), cube_map);
	cub->m->pattern->transform = mmultfree(scaling(1, 1, 1), cub->m->pattern->transform);
	cub->m->pattern->transform = mmultfree(translation(0, 0, 0), cub->m->pattern->transform);
	cub->m->pattern->transform = mmultfree(rotation_z(90 * DEG2RAD), cub->m->pattern->transform);
	cub->m->pattern->invtrans = minvert(cub->m->pattern->transform, 4);
	
	hex = hexagon();
	hex->transform = mmultfree(scaling(1, 1, 1), hex->transform);
	hex->transform = mmultfree(translation(3.5, .2, 0), hex->transform);
	hex->invtrans = minvert(hex->transform, 4);

	w.light = ft_calloc(3, sizeof(t_light *));
	if (!w.light)
		exit (1);
	w.light[0] = point_light(point(-7, 7, -6), color(200, 200, 180));
	w.light[0]->last = false;
	w.light[1] = point_light(point(-4, 8, 2), color(180, 120, 120));

	w.s = ft_calloc(9, sizeof(t_shape *));
	w.s[0] = floor;
	w.s[1] = big;
	w.s[2] = middle;
	w.s[3] = right;
	w.s[4] = left;
	w.s[5] = cub;
	w.s[6] = hex;
	return (w);
}

t_world	default_world_group_test(void)
{
	t_world	w;
//	t_shape	*floor;
	t_shape	*hex;
	t_light	*light;
/*	
	floor = plane();
	floor->m->color = color(200, 200, 200);
	floor->m.diffuse = 0.4;
	floor->m.ambient = 0;
	floor->m.specular = 0.2;
	floor->m.reflective = .2;
	free_matrix(floor->m.pattern.transform, 4);
	free_matrix(floor->m.pattern.invtrans, 4);
	floor->m.pattern = checkers_pattern(color(0, 0, 0), floor->m->color);
*/
	hex = hexagon();
	set_transform(hex, translation(0, 1, 0));
	hex->m->color = color(0, 50, 100);
	hex->m->diffuse = 0.3;
	hex->m->ambient = 0.2;
	hex->m->specular = 0;
	hex->m->reflective = 0;

	light = point_light(point(-7, 7, -6), color(255, 255, 255));
	w.s = calloc(4, sizeof(*w.s));
	if (!w.s)
		exit (1);
//	w.s[0] = floor;
	w.s[0] = hex;
	w.light = ft_calloc(2, sizeof(t_light *));
	if (!w.light)
		exit (1);
	w.light[0] = light;
	return (w);
}
