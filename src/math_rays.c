/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:55:04 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/30 22:55:02 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray(t_tuple point, t_tuple vector)
{
	t_ray	ray;

	ray.origin = point;
	ray.direction = vector;
	return (ray);
}

t_tuple	position(t_ray ray, float t)
{
	t_tuple	position;

	position = tadd(ray.origin, tmult(ray.direction, t));
	return (position);
}

float	*intersect(t_sphere s, t_ray r)
{
	t_tuple	sphere_to_ray;
	float a;
	float b;
	float discriminant;
	float *t;

	t = malloc(2 * sizeof(float));
		if (!t)
			exit (1);  //TODO FREE
	sphere_to_ray = tsub(r.origin, s.origin);
	a = dot(r.direction, r.direction);
	b = 2 * dot(r.direction, sphere_to_ray);
	discriminant = powf(b, 2) - 4 * a * (dot(sphere_to_ray, sphere_to_ray) - 1);
	if (discriminant < 0)
	{
		free(t);
		return (NULL);
	}
	t[0] = (-b - sqrtf(discriminant)) / (2 * a);
	t[1] = (-b + sqrtf(discriminant)) / (2 * a);
	return (t);
}
