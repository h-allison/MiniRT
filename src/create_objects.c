/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:39 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/19 13:01:41 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// TODO REMOVE TEST FUNCTIONS 

t_shape	create_test_shape(void)
{
	t_shape	s;

	s.parent = NULL;
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

	s.parent = NULL;
	s.transform = create_id_matrix();
	s.invtrans = minvert(s.transform, 4);
	s.local_normal_at = local_normal_at_sphere;
	s.local_intersect = local_intersect_sphere;
	s.m = material();
	s.m.transparency = 1.0;
	s.m.refractive_index = 1.5;
	return (s);
}

//TODO ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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

t_shape	group(void)
{
	t_shape	g;

	g.transform = create_id_matrix();
	g.invtrans = minvert(g.transform, 4);
	g.local_normal_at = NULL;
	g.local_intersect = NULL;
	g.group = NULL;
	return (g);
}

t_shape	sphere(void)
{
	t_shape	s;

	s.parent = NULL;
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

	s.parent = NULL;
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

	s.parent = NULL;
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

	s.parent = NULL;
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

	s.parent = NULL;
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

