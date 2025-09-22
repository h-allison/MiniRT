/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:13:39 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/22 20:59:49 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* TEST FUNCTIONS, PROTOTYPES */

t_shape	create_test_shape(void)
{
	t_shape	*s;

	s = malloc(sizeof(*s));
	s->parent = NULL;
	s->group = NULL;
	s->transform = create_id_matrix();
	s->invtrans = minvert(s->transform, 4);
	s->local_normal_at = local_normal_at;
	s->local_intersect = local_intersect;
	s->m = material();
	return (*s);
}

t_pattern	create_test_pattern(void)
{
	t_pattern	*pat;

	pat = malloc(sizeof(*pat));
	pat->a = color(255, 255, 255);
	pat->b = color(0, 0, 0);
	pat->transform = create_id_matrix();
	pat->invtrans = minvert(pat->transform, 4);
	pat->pattern_at = &pattern_at;
	pat->status = true;
	return (*pat);
}

t_shape	glass_sphere(void)
{
	t_shape	*s;

	s = malloc(sizeof(*s));
	s->parent = NULL;
	s->group = NULL;
	s->transform = create_id_matrix();
	s->invtrans = minvert(s->transform, 4);
	s->local_normal_at = local_normal_at_sphere;
	s->local_intersect = local_intersect_sphere;
	s->m = material();
	s->m.transparency = 1.0;
	s->m.refractive_index = 1.5;
	return (*s);
}

/* CREATE BASICS */

t_camera	camera(float hsize, float vsize, float field_of_view)
{
	t_camera	*c;
	float		half_view;
	float		aspect;

	c = malloc(sizeof(*c));
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
	return (*c);
}

t_light	point_light(t_tuple position, t_rgb intensity)
{
	t_light	*light;

	light = malloc(sizeof(*light));
	light->position = position;
	light->intensity = intensity;
	light->last = true;
	return (*light);
}

t_pattern	pattern(void)
{
	t_pattern	*p;

	p = malloc(sizeof(*p));
	p->a = color(255, 255, 255);
	p->b = color(0, 0, 0);
	p->transform = create_id_matrix();
	p->invtrans = minvert(p->transform, 4);
	p->status = false;
	return (*p);
}

t_material	material(void)
{
	t_material	*m;

	m = malloc(sizeof(*m));
	m->color = color(0xFF, 0xFF, 0xFF);
	m->ambient = 0.1;
	m->diffuse = 0.9;
	m->specular = 0.9;
	m->shininess = 200;
	m->reflective = 0.0;
	m->transparency = 0.0;
	m->refractive_index = 1.0;
	m->pattern = pattern();
	return (*m);
}

t_shape	group(void)
{
	t_shape	*g;

	g = malloc(sizeof(*g));
	g->parent = NULL;
	g->group = NULL;
	g->transform = create_id_matrix();
	g->invtrans = minvert(g->transform, 4);
	g->local_normal_at = local_normal_at_group;
	g->local_intersect = local_intersect_group;
	g->m = material();
	return (*g);
}

/* CREATE VARIOUS SHAPES */

t_shape	sphere(void)
{
	t_shape	*s;

	s = malloc(sizeof(*s));
	s->parent = NULL;
	s->group = NULL;
	s->transform = create_id_matrix();
	s->invtrans = minvert(s->transform, 4);
	s->local_normal_at = local_normal_at_sphere;
	s->local_intersect = local_intersect_sphere;
	s->m = material();
	return (*s);
}

t_shape	plane(void)
{
	t_shape	*s;

	s = malloc(sizeof(*s));
	s->parent = NULL;
	s->group = NULL;
	s->transform = create_id_matrix();
	s->invtrans = minvert(s->transform, 4);
	s->local_normal_at = local_normal_at_plane;
	s->local_intersect = local_intersect_plane;
	s->m = material();
	return (*s);
}

t_shape	cube(void)
{
	t_shape	*s;

	s = malloc(sizeof(*s));
	s->parent = NULL;
	s->group = NULL;
	s->transform = create_id_matrix();
	s->invtrans = minvert(s->transform, 4);
	s->local_normal_at = local_normal_at_cube;
	s->local_intersect = local_intersect_cube;
	s->m = material();
	return (*s);
}

t_shape	cylinder(void)
{
	t_shape	*s;

	s = malloc(sizeof(*s));
	s->parent = NULL;
	s->group = NULL;
	s->transform = create_id_matrix();
	s->invtrans = minvert(s->transform, 4);
	s->local_normal_at = local_normal_at_cyl;
	s->local_intersect = local_intersect_cyl;
	s->m = material();
	s->minimum = -FLT_MAX;
	s->maximum = FLT_MAX;
	s->closed = false;
	return (*s);
}

t_shape	cone(void)
{
	t_shape	*s;

	s = malloc(sizeof(*s));
	s->parent = NULL;
	s->group = NULL;
	s->transform = create_id_matrix();
	s->invtrans = minvert(s->transform, 4);
	s->local_normal_at = local_normal_at_cone;
	s->local_intersect = local_intersect_cone;
	s->m = material();
	s->minimum = -FLT_MAX;
	s->maximum = FLT_MAX;
	s->closed = false;
	return (*s);
}

/* GROUPED OBJECTS */

static t_shape	hexagon_corner(void)
{
	t_shape	*corner;

	corner = malloc(sizeof(*corner));
	*corner = sphere();
	corner->m.color = color(0, 50, 100);
	corner->m.diffuse = 0.8;
	corner->m.ambient = 0.7;
	corner->m.specular = 0.2;
	set_transform(corner, mmultfree(translation(0, 0, 1),
			scaling(0.25, 0.25, 0.25)));
	return (*corner);
}

static t_shape	hexagon_edge(void)
{
	t_shape	*edge;
	float	**t;

	edge = malloc(sizeof(*edge));
	*edge = cylinder();
	edge->minimum = 0;
	edge->maximum = 1;
	edge->m.color = color(0, 50, 100);
	edge->m.diffuse = 0.8;
	edge->m.ambient = 0.7;
	edge->m.specular = 0.2;
	edge->m.pattern = stripe_pattern(color(180, 80, 0), edge->m.color);
	t = scaling(0.25, 1, 0.25);
	t = mmultfree(rotation_z(-(M_PI / 2)), t);
	t = mmultfree(rotation_y(-(M_PI / 6)), t);
	t = mmultfree(translation(0, 0, -1), t);
	set_transform(edge, t);
	return (*edge);
}

static t_shape	hexagon_side(void)
{
	t_shape	*side;
	t_shape	*corner;
	t_shape	*edge;

	side = malloc(sizeof(*side));
	corner = malloc(sizeof(*corner));
	edge = malloc(sizeof(*edge));
	if (!corner || !edge || !side)
		exit(1);
	*corner = hexagon_corner();
	*edge = hexagon_edge();
	*side = group();
	add_child(side, corner);
	add_child(side, edge);
	return (*side);
}

t_shape	hexagon(void)
{
	t_shape	*hex;
	t_shape	*side;
	int		n;

	side = malloc(6 * sizeof(*side));
	hex = malloc(6 * sizeof(*hex));
	if (!side || !hex)
		exit(1);
	n = 0;
	*hex = group();
	while (n < 6)
	{
		side[n] = hexagon_side();
		side[n].transform = mmultfree(rotation_y(n * M_PI / 3),
				side[n].transform);
		free_matrix(side[n].invtrans, 4);
		side[n].invtrans = minvert(side[n].transform, 4);
		add_child(hex, &side[n]);
		n++;
	}
	return (*hex);
}
