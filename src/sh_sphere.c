/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:48:28 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 18:20:42 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*sphere(void)
{
	t_shape	*s;

	s = malloc(sizeof(t_shape));
	s->parent = NULL;
	s->group = NULL;
	s->triangle = NULL;
	s->transform = create_id_matrix();
	s->invtrans = minvert(s->transform, 4);
	s->local_normal_at = local_normal_at_sphere;
	s->local_intersect = local_intersect_sphere;
	s->m = material();
	return (s);
}

t_tuple	local_normal_at_sphere(t_shape *s, t_tuple local_point)
{
	t_tuple	local_normal;

	(void)s;
	local_normal = tsub(local_point, point(0, 0, 0));
	return (local_normal);
}

t_intersection	*local_intersect_sphere(t_shape *s, t_ray r)
{
	t_tuple			sphere_to_ray;
	float			a;
	float			b;
	float			discriminant;
	t_intersection	*xs;

	sphere_to_ray = tsub(r.origin, point(0, 0, 0));
	a = dot(r.direction, r.direction);
	b = 2 * dot(r.direction, sphere_to_ray);
	discriminant = b * b - 4 * a * (dot(sphere_to_ray, sphere_to_ray) - 1);
	if (discriminant < 0)
		xs = intersections(intersection(0, NULL), intersection(0, NULL));
	else
		xs = intersections(intersection((-b - sqrtf(discriminant))
					/ (2 * a), s), intersection((-b + sqrtf(discriminant))
					/ (2 * a), s));
	return (xs);
}
