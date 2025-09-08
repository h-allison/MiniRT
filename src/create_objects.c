/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 21:14:22 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/08 14:41:34 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_object	sphere(void)
{
	t_object	sphere;

	sphere.objtype = OBJ_SPHERE; 
	sphere.transform = create_id_matrix();
	sphere.m.color = color(0xFF, 0xFF, 0xFF);
	sphere.m.ambient = 0.1;
	sphere.m.diffuse = 0.9;
	sphere.m.specular = 0.9;
	sphere.m.shininess = 200;
	return (sphere);
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
	t_object	s1;
	t_object	s2;
	t_light		light;

	light = point_light(point(-10, 10, -10), color(255, 255, 255));
	s1 = sphere();
	s1.m.color = color(204, 255, 153);
	s1.m.diffuse = 0.7;
	s1.m.specular = 0.2;
	s2 = sphere();
	s2.transform = mmultfree(scaling(0.5, 0.5, 0.5), s2.transform);
	w.s = malloc(3 * sizeof(t_object));
	w.s[0] = s1;
	w.s[1] = s2;
	w.s[2].transform = NULL;
	w.light = malloc(sizeof(t_light));
	if (!w.light)
		exit (1);
	w.light[0] = light;
	return (w);
}
