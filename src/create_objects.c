/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:39 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 19:50:11 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* CREATE BASICS */

t_camera	*camera(float hsize, float vsize, float field_of_view)
{
	t_camera	*c;
	float		half_view;
	float		aspect;

	c = malloc(sizeof(t_camera));
	c->hsize = hsize;
	c->vsize = vsize;
	c->field_of_view = field_of_view;
	c->transform = create_id_matrix();
	half_view = tanf(field_of_view / 2);
	aspect = hsize / vsize;
	if (aspect >= 1)
	{
		c->half_width = half_view;
		c->half_height = half_view / aspect;
	}
	if (aspect < 1)
	{
		c->half_width = half_view * aspect;
		c->half_height = half_view;
	}
	c->pixel_size = (c->half_width * 2) / c->hsize;
	return (c);
}

t_light	*point_light(t_tuple position, t_rgb intensity)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	light->position = position;
	light->intensity = intensity;
	light->last = true;
	return (light);
}

t_pattern	*pattern(void)
{
	t_pattern	*p;

	p = malloc(sizeof(t_pattern));
	p->a = color(255, 255, 255);
	p->b = color(0, 0, 0);
	p->transform = create_id_matrix();
	p->invtrans = minvert(p->transform, 4);
	p->uv_pattern = NULL;
	p->canvas = NULL;
	p->status = false;
	return (p);
}

t_material	*material(void)
{
	t_material	*m;

	m = malloc(sizeof(t_material));
	m->color = color(0xFF, 0xFF, 0xFF);
	m->ambient = 0.1;
	m->diffuse = 0.9;
	m->specular = 0.9;
	m->shininess = 200;
	m->reflective = 0.0;
	m->transparency = 0.0;
	m->refractive_index = 1.0;
	m->pattern = pattern();
	return (m);
}
