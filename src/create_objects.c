/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:39 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/18 17:10:20 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	pattern(void)
{
	t_pattern	p;

	p.a = color(255, 255, 255);
	p.b = color(0, 0, 0);
	p.transform = create_id_matrix();
	p.invtrans = minvert(p.transform, 4);
	p.status = false;
	return (p);
}

t_material	material(void)
{
	t_material	m;

	m.color = color(0xFF, 0xFF, 0xFF);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	m.reflective = 0.0;
	m.transparency = 0.0;
	m.refractive_index = 1.0;
	m.pattern = pattern();
	return(m);
}

t_shape	create_test_shape(void)
{
	t_shape	s;

	s.transform = create_id_matrix();
	s.invtrans = minvert(s.transform, 4);
	s.local_normal_at = local_normal_at;
	s.local_intersect = local_intersect;
	s.m = material();
	return(s);
}

t_pattern	create_test_pattern(void)
{
	t_pattern	pat;

	pat.a = color(255, 255, 255);
	pat.b = color(0, 0, 0);
	pat.transform = create_id_matrix();
	pat.invtrans = minvert(pat.transform, 4);
	pat.pattern_at = &pattern_at;
	pat.status = true;
	return(pat);
}

t_shape	glass_sphere(void)
{
	t_shape	s;

	s.transform = create_id_matrix();
	s.invtrans = minvert(s.transform, 4);
	s.local_normal_at = local_normal_at_sphere;
	s.local_intersect = local_intersect_sphere;
	s.m = material();
	s.m.transparency = 1.0;
	s.m.refractive_index = 1.5;
	return (s);
}

t_shape	sphere(void)
{
	t_shape	s;

	s.transform = create_id_matrix();
	s.invtrans = minvert(s.transform, 4);
	s.local_normal_at = local_normal_at_sphere;
	s.local_intersect = local_intersect_sphere;
	s.m = material();
	return (s);
}

t_shape	plane(void)
{
	t_shape	s;

	s.transform = create_id_matrix();
	s.invtrans = minvert(s.transform, 4);
	s.local_normal_at = local_normal_at_plane;
	s.local_intersect = local_intersect_plane;
	s.m = material();
	return (s);
}

t_shape	cube(void)
{
	t_shape	s;

	s.transform = create_id_matrix();
	s.invtrans = minvert(s.transform, 4);
	s.local_normal_at = local_normal_at_cube;
	s.local_intersect = local_intersect_cube;
	s.m = material();
	return (s);
}

t_shape	cylinder(void)
{
	t_shape	s;

	s.transform = create_id_matrix();
	s.invtrans = minvert(s.transform, 4);
	s.local_normal_at = local_normal_at_cyl;
	s.local_intersect = local_intersect_cyl;
	s.m = material();
	s.minimum = -FLT_MAX;
	s.maximum = FLT_MAX;
	s.closed = false;
	return (s);
}

t_shape	cone(void)
{
	t_shape	s;

	s.transform = create_id_matrix();
	s.invtrans = minvert(s.transform, 4);
	s.local_normal_at = local_normal_at_cone;
	s.local_intersect = local_intersect_cone;
	s.m = material();
	s.minimum = -FLT_MAX;
	s.maximum = FLT_MAX;
	s.closed = false;
	return (s);
}

t_light	point_light(t_tuple position, t_rgb intensity)
{
	t_light	light;

	light.position = position;
	light.intensity = intensity;
	light.last = true;
	return (light);
}

t_camera	camera(float hsize, float vsize, float field_of_view)
{
	t_camera	c;
	float		half_view;
	float		aspect;
	
	c.hsize = hsize;
	c.vsize = vsize;
	c.field_of_view = field_of_view;
	c.transform = create_id_matrix();
	half_view = tanf(field_of_view / 2);
	aspect = hsize / vsize;
	if (aspect >= 1)
	{
		c.half_width = half_view;
		c.half_height = half_view / aspect;
	}
	if (aspect < 1)
	{
		c.half_width = half_view * aspect;
		c.half_height = half_view;
	}
	c.pixel_size = (c.half_width * 2) / c.hsize;
	return (c);
}

t_world	default_world(void)
{
	t_world	w;
	t_shape	s1;
	t_shape	s2;
	t_light	light;

	light = point_light(point(-10, 10, -10), color(255, 255, 255));
	s1 = sphere();
	s1.m.color = color(204, 255, 153);
	s1.m.diffuse = 0.7;
	s1.m.specular = 0.2;
	s2 = sphere();
	set_transform(&s2, scaling(0.5, 0.5, 0.5));
	s2.invtrans = minvert(s2.transform, 4);
	w.s = malloc(5 * sizeof(t_shape));
	w.s[0] = s1;
	w.s[1] = s2;
	w.s[2].transform = NULL;
	w.light = malloc(sizeof(t_light));
	if (!w.light)
		exit (1);
	w.light[0] = light;
	return (w);
}

t_world	default_world_2(void)
{
	t_world		w;
	t_shape	floor;
	t_shape	left_wall;
	t_shape	right_wall;
	t_shape	middle;
	t_shape	right;
	t_shape	left;

	floor = sphere();
	floor.transform = mmultfree(scaling(10, 0.01, 10), floor.transform);
	floor.invtrans = minvert(floor.transform, 4);
	floor.m.color = color(255, 230, 230);
	floor.m.specular = 0;

	left_wall = sphere();
	left_wall.transform = mmultfree(scaling(10, 0.01, 10), left_wall.transform);
	left_wall.transform = mmultfree(rotation_x(M_PI / 2), left_wall.transform);
	left_wall.transform = mmultfree(rotation_y(-M_PI / 4), left_wall.transform);
	left_wall.transform = mmultfree(translation(0, 0, 5), left_wall.transform);
	left_wall.invtrans = minvert(left_wall.transform, 4);
	left_wall.m = floor.m;

	right_wall = sphere();
	right_wall.transform = mmultfree(scaling(10, 0.01, 10), right_wall.transform);
	right_wall.transform = mmultfree(rotation_x(M_PI / 2), right_wall.transform);
	right_wall.transform = mmultfree(rotation_y(M_PI / 4), right_wall.transform);
	right_wall.transform = mmultfree(translation(0, 0, 5), right_wall.transform);
	right_wall.invtrans = minvert(right_wall.transform, 4);
	right_wall.m = floor.m;

	middle = sphere();
	middle.transform = mmultfree(translation(-0.5, 1, 0.5), middle.transform);
	middle.invtrans = minvert(middle.transform, 4);
	middle.m.color = color(26, 255, 128);
	middle.m.diffuse = 0.7;
	middle.m.specular = 0.3;

	right = sphere();
	right.transform = mmultfree(scaling(0.5, 0.5, 0.5), right.transform);
	right.transform = mmultfree(translation(1.5, 0.5, -0.5), right.transform);
	right.invtrans = minvert(right.transform, 4);
	right.m.color = color(128, 255, 26);
	right.m.diffuse = 0.7;
	right.m.specular = 0.3;

	left = sphere();
	left.transform = mmultfree(scaling(0.33, 0.33, 0.33), left.transform);
	left.transform = mmultfree(translation(-1.5, 0.33, -0.75), left.transform);
	left.invtrans = minvert(left.transform, 4);
	left.m.color = color(255, 204, 26);
	left.m.diffuse = 0.7;
	left.m.specular = 0.3;

	w.light = malloc(sizeof(t_light));
	if (!w.light)
		exit (1);
	w.light[0] = point_light(point(-10, 10, -10), color(255, 255, 255));

	w.s = malloc(7 * sizeof(t_shape));
	w.s[0] = floor;
	w.s[1] = left_wall;
	w.s[2] = right_wall;
	w.s[3] = middle;
	w.s[4] = right;
	w.s[5] = left;
	w.s[6].transform = NULL;
	return (w);
}

t_world	default_world_3(void)
{
	t_world		w;
	t_shape	floor;
	t_shape	middle;
	t_shape	right;
	t_shape	left;

	floor = plane();
	floor.invtrans = minvert(floor.transform, 4);
	floor.m.color = color(255, 230, 230);
	floor.m.diffuse = .4;
	floor.m.ambient = 0;
	floor.m.specular = 0;
	floor.m.pattern = stripe_pattern(color(160, 130, 130), floor.m.color);

	middle = sphere();
	middle.transform = mmultfree(translation(-0.5, 1, 0.5), middle.transform);
	middle.invtrans = minvert(middle.transform, 4);
	middle.m.color = color(26, 150, 200);
	middle.m.diffuse = 0.7;
	middle.m.specular = 0.3;

	right = sphere();
	right.transform = mmultfree(scaling(0.5, 0.5, 0.5), right.transform);
	right.transform = mmultfree(translation(1.5, 0.5, -0.5), right.transform);
	right.invtrans = minvert(right.transform, 4);
	right.m.color = color(128, 255, 26);
	right.m.diffuse = 0.7;
	right.m.specular = 0.3;

	left = sphere();
	left.transform = mmultfree(scaling(0.33, 0.33, 0.33), left.transform);
	left.transform = mmultfree(translation(-1.5, 0.33, -0.75), left.transform);
	left.invtrans = minvert(left.transform, 4);
	left.m.color = color(255, 204, 26);
	left.m.diffuse = 0.7;
	left.m.specular = 0.3;

	w.light = malloc(sizeof(t_light));
	if (!w.light)
		exit (1);
	w.light[0] = point_light(point(-10, 10, -10), color(255, 255, 255));

	w.s = malloc(5 * sizeof(t_shape));
	w.s[0] = floor;
	w.s[1] = middle;
	w.s[2] = right;
	w.s[3] = left;
	w.s[4].transform = NULL;
	return (w);
}

t_world	default_world_4(void)
{
	t_world		w;
	t_shape	floor;
	t_shape	wall_back;
	t_shape	middle;
	t_shape	right;
	t_shape	left;
	
	floor = plane();
	floor.invtrans = minvert(floor.transform, 4);
	floor.m.color = color(200, 200, 200);
	floor.m.diffuse = 0.7;
	floor.m.ambient = 0.0;
	floor.m.specular = 0.1;
	floor.m.reflective = 0.1;
	floor.m.pattern = checkers_pattern(color(100, 80, 60), floor.m.color);

	wall_back = plane();
	wall_back.transform = mmultfree(rotation_x(M_PI / 2), wall_back.transform);
	wall_back.transform = mmultfree(translation(0, 0, 40), wall_back.transform);
	wall_back.invtrans = minvert(wall_back.transform, 4);
	wall_back.m.color = color(80, 0, 0);
	wall_back.m.diffuse = 0.5;
	wall_back.m.ambient = 0;
	wall_back.m.specular = 0;
	wall_back.m.pattern = gradient_pattern(wall_back.m.color, color(0, 0, 180)) ; 
	wall_back.m.pattern.transform = mmultfree(scaling(18, 1, 1), wall_back.m.pattern.transform);
	wall_back.m.pattern.transform = mmultfree(rotation_y(90 * DEG2RAD), wall_back.m.pattern.transform);
	wall_back.m.pattern.invtrans = minvert(wall_back.m.pattern.transform, 4);

	left = sphere();
	left.transform = mmultfree(scaling(0.33, 0.33, 0.33), left.transform);
	left.transform = mmultfree(translation(-1.5, 0.33, -0.75), left.transform);
	left.invtrans = minvert(left.transform, 4);
	left.m.color = color(255, 128, 128);
	left.m.diffuse = 0.7;
	left.m.specular = 0.5;

	middle = sphere();
	middle.transform = mmultfree(translation(-0.5, 1, 1.5), middle.transform);
	middle.invtrans = minvert(middle.transform, 4);
	middle.m.color = color(10, 10, 10);
	middle.m.diffuse = 1;
	middle.m.specular = 0.1;
	middle.m.reflective = 1;

	right = sphere();
	right.transform = mmultfree(scaling(0.5, 0.5, 0.5), right.transform);
	right.transform = mmultfree(translation(1.5, 0.5, -0.5), right.transform);
	right.invtrans = minvert(right.transform, 4);
	right.m.color = color(140, 100, 255);
	right.m.diffuse = 0.7;
	right.m.specular = 0.4;
	right.m.pattern = ring_pattern(color(20, 80, 60), right.m.color);
	right.m.pattern.transform = mmultfree(scaling(0.1, 0.2, 0.2), right.m.pattern.transform);
	right.m.pattern.invtrans = minvert(right.m.pattern.transform, 4);
	
	w.light = malloc(3 * sizeof(t_light));
	if (!w.light)
		exit (1);
	w.light[0] = point_light(point(-7, 7, -6), color(160, 40, 40));
	w.light[0].last = false;
	w.light[1] = point_light(point(7, 7, -6), color(40, 40, 160));
	w.light[1].last = false;
	w.light[2] = point_light(point(-2, 3, -6), color(40, 160, 40));

	w.s = malloc(8 * sizeof(t_shape));
	w.s[0] = floor;
	w.s[1] = wall_back;
	w.s[2] = middle;
	w.s[3] = right;
	w.s[4] = left;
	w.s[5].transform = NULL;
	return (w);
}

t_world	default_world_5(void)
{
	t_world	w;
	t_shape	floor;
	t_shape	big;
	t_shape	middle;
	t_shape	right;
	t_shape	left;
	
	floor = plane();
	floor.invtrans = minvert(floor.transform, 4);
	floor.m.color = color(200, 200, 200);
	floor.m.diffuse = 0.7;
	floor.m.ambient = 0.01;
	floor.m.specular = 0.1;
	floor.m.reflective = .1;
	floor.m.pattern = ring_pattern(color(80, 80, 80), floor.m.color);

	big = plane();
	big.transform = mmultfree(translation(0, 8, 8), big.transform);
	big.transform = mmultfree(rotation_x(80 * DEG2RAD), big.transform);
	big.transform = mmultfree(rotation_y(20 * DEG2RAD), big.transform);
	big.invtrans = minvert(big.transform, 4);
	big.m.color = color(220, 230, 255);
	big.m.diffuse = .1;
	big.m.ambient = 0;
	big.m.specular = 0;
	big.m.reflective = 0.7;

	left = sphere();
	left.transform = mmultfree(scaling(0.33, 0.33, 0.33), left.transform);
	left.transform = mmultfree(translation(-2, 0.33, 0), left.transform);
	left.invtrans = minvert(left.transform, 4);
	left.m.color = color(255, 128, 128);
	left.m.diffuse = 0.7;
	left.m.specular = 0.5;

	middle = sphere();
	middle.transform = mmultfree(translation(-0.2, 1, 1), middle.transform);
	middle.invtrans = minvert(middle.transform, 4);
	middle.m.color = color(138, 132, 70);
	middle.m.diffuse = 0.1;
	middle.m.specular = 0.2;
	middle.m.reflective = 0.8;

	right = sphere();
	right.transform = mmultfree(scaling(0.5, 0.5, 0.5), right.transform);
	right.transform = mmultfree(translation(1.5, 0.5, -1), right.transform);
	right.invtrans = minvert(right.transform, 4);
	right.m.color = color(140, 100, 255);
	right.m.diffuse = 0.7;
	right.m.specular = 0.4;
	right.m.pattern = ring_pattern(color(20, 80, 60), right.m.color);
	right.m.pattern.transform = mmultfree(scaling(0.1, 0.2, 0.2), right.m.pattern.transform);
	right.m.pattern.invtrans = minvert(right.m.pattern.transform, 4);
	
	w.light = malloc(1 * sizeof(t_light));
	if (!w.light)
		exit (1);
	w.light[0] = point_light(point(-7, 7, -6), color(255, 255, 240));

	w.s = malloc(8 * sizeof(t_shape));
	w.s[0] = floor;
	w.s[1] = big;
	w.s[2] = middle;
	w.s[3] = right;
	w.s[4] = left;
	w.s[5].transform = NULL;
	return (w);
}
