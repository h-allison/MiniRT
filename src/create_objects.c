/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:14:22 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/10 03:04:15 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_material	material(void)
{
	t_material	m;

	m.color = color(0xFF, 0xFF, 0xFF);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200;
	return(m);
}

t_shape	create_test_shape(void)
{
	t_shape	s;

	s.transform = create_id_matrix();
	s.m = material();
	return(s);
}

t_shape	sphere(void)
{
	t_shape	s;

	s.type = OBJ_SPHERE; 
	s.transform = create_id_matrix();
	s.m = material();
	return (s);
}

t_light	point_light(t_tuple position, t_rgb intensity)
{
	t_light	light;

	light.position = position;
	light.intensity = intensity;
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
	s2.transform = mmultfree(scaling(0.5, 0.5, 0.5), s2.transform);
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
	floor.m.color = color(255, 230, 230);
	floor.m.specular = 0;

	left_wall = sphere();
	left_wall.transform = mmultfree(scaling(10, 0.01, 10), left_wall.transform);
	left_wall.transform = mmultfree(rotation_x(M_PI / 2), left_wall.transform);
	left_wall.transform = mmultfree(rotation_y(-M_PI / 4), left_wall.transform);
	left_wall.transform = mmultfree(translation(0, 0, 5), left_wall.transform);
	left_wall.m = floor.m;

	right_wall = sphere();
	right_wall.transform = mmultfree(scaling(10, 0.01, 10), right_wall.transform);
	right_wall.transform = mmultfree(rotation_x(M_PI / 2), right_wall.transform);
	right_wall.transform = mmultfree(rotation_y(M_PI / 4), right_wall.transform);
	right_wall.transform = mmultfree(translation(0, 0, 5), right_wall.transform);
	right_wall.m = floor.m;

	middle = sphere();
	middle.transform = mmultfree(translation(-0.5, 1, 0.5), middle.transform);
	middle.m.color = color(26, 255, 128);
	middle.m.diffuse = 0.7;
	middle.m.specular = 0.3;

	right = sphere();
	right.transform = mmultfree(scaling(0.5, 0.5, 0.5), right.transform);
	right.transform = mmultfree(translation(1.5, 0.5, -0.5), right.transform);
	right.m.color = color(128, 255, 26);
	right.m.diffuse = 0.7;
	right.m.specular = 0.3;

	left = sphere();
	left.transform = mmultfree(scaling(0.33, 0.33, 0.33), left.transform);
	left.transform = mmultfree(translation(-1.5, 0.33, -0.75), left.transform);
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
