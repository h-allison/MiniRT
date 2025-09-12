/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 14:49:07 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/12 21:32:13 by mmillhof         ###   ########.fr       */
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

	pat.transform = create_id_matrix();
	pat.invtrans = minvert(pat.transform, 4);
	return(pat);
}

t_shape	sphere(void)
{
	t_shape	s;

	s.type = OBJ_SPHERE; 
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

	s.type = OBJ_PLANE; 
	s.transform = create_id_matrix();
	s.invtrans = minvert(s.transform, 4);
	s.local_normal_at = local_normal_at_plane;
	s.local_intersect = local_intersect_plane;
	s.m = material();
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
	t_world		w;
	t_shape	s1;
	t_shape	s2;
	t_light		light;

	light = point_light(point(-10, 10, -10), color(255, 255, 255));
	s1 = sphere();
	s1.m.color = color(204, 255, 153);
	s1.m.diffuse = 0.7;
	s1.m.specular = 0.2;
	s2 = sphere();
	set_transform(&s2, scaling(0.5, 0.5, 0.5));
	w.s = malloc(3 * sizeof(t_shape));
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
	t_shape	ceiling;
	t_shape	wall_back;
	t_shape	wall_left;
	t_shape	middle;
	t_shape	right;
	t_shape	left;

	floor = plane();
	floor.invtrans = minvert(floor.transform, 4);
	floor.m.color = color(200, 200, 200);
	floor.m.diffuse = 0.7;
	floor.m.ambient = 0.1;
	floor.m.specular = 0.1;
	floor.m.pattern = stripe_pattern(color(100, 80, 60), floor.m.color);

	ceiling = plane();
	ceiling.transform = mmultfree(translation(0, 7, 0), ceiling.transform);
	ceiling.invtrans = minvert(floor.transform, 4);
	ceiling.m.color = color(200, 200, 200);
	ceiling.m.diffuse = 0.7;
	ceiling.m.ambient = 0.1;
	ceiling.m.specular = 0.1;
	ceiling.m.pattern = stripe_pattern(color(100, 80, 60), floor.m.color);

	wall_back = plane();
	wall_back.transform = mmultfree(rotation_x(M_PI / 2), wall_back.transform);
	wall_back.transform = mmultfree(translation(0, 0, 20), wall_back.transform);
	wall_back.invtrans = minvert(wall_back.transform, 4);
	wall_back.m.color = color(180, 120, 180);
	wall_back.m.diffuse = 0.5;
	wall_back.m.ambient = 0.0;
	wall_back.m.specular = 0.0;

	wall_left = plane();
	wall_left.transform = mmultfree(rotation_x(M_PI / 2), wall_left.transform);
	wall_left.transform = mmultfree(rotation_y(M_PI / 2), wall_left.transform);
	wall_left.transform = mmultfree(translation(-12, 0, 0), wall_left.transform);
	wall_left.invtrans = minvert(wall_left.transform, 4);
	wall_left.m.color = color(160, 160, 160);
	wall_left.m.diffuse = 0.5;
	wall_left.m.ambient = 0.0;
	wall_left.m.specular = 0.1;

	left = sphere();
	left.transform = mmultfree(scaling(0.33, 0.33, 0.33), left.transform);
	left.transform = mmultfree(translation(-1.5, 0.33, -0.75), left.transform);
	left.invtrans = minvert(left.transform, 4);
	left.m.color = color(255, 128, 128);
	left.m.diffuse = 0.7;
	left.m.specular = 0.5;

	middle = sphere();
	middle.transform = mmultfree(translation(-0.5, 1, 0.5), middle.transform);
	middle.invtrans = minvert(middle.transform, 4);
	middle.m.color = color(128, 255, 128);
	middle.m.diffuse = 0.5;
	middle.m.specular = 0.6;

	right = sphere();
	right.transform = mmultfree(scaling(0.5, 0.5, 0.5), right.transform);
	right.transform = mmultfree(translation(1.5, 0.5, -0.5), right.transform);
	right.invtrans = minvert(right.transform, 4);
	right.m.color = color(255, 255, 255);
	right.m.diffuse = 0.7;
	right.m.specular = 0.4;
	right.m.pattern = stripe_pattern(color(20, 80, 60), right.m.color);
	right.m.pattern.transform = mmultfree(scaling(0.1, 0.1, 0.1), right.m.pattern.transform);
	right.m.pattern.transform = mmultfree(rotation_y(300 * DEG2RAD), right.m.pattern.transform);
	right.m.pattern.transform = mmultfree(rotation_x(90 * DEG2RAD), right.m.pattern.transform);
	right.m.pattern.invtrans = minvert(right.m.pattern.transform, 4);

	w.light = malloc(3 * sizeof(t_light));
	if (!w.light)
		exit (1);
	w.light[0] = point_light(point(-7, 7, -10), color(160, 40, 40));
	w.light[0].last = false;
	w.light[1] = point_light(point(7, 7, -10), color(40, 40, 160));
	w.light[1].last = false;
	w.light[2] = point_light(point(-2, 3, -10), color(40, 160, 40));

	w.s = malloc(8 * sizeof(t_shape));
	w.s[0] = floor;
	w.s[1] = ceiling;
	w.s[2] = wall_back;
	w.s[3] = wall_left;
	w.s[4] = middle;
	w.s[5] = right;
	w.s[6] = left;
	w.s[7].transform = NULL;
	return (w);
}
