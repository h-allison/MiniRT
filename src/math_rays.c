/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:55:04 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 16:40:53 by hallison         ###   ########.fr       */
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

t_ray	transform(t_ray r, float **m)
{
	t_ray	r2;

	r2.origin = tmatrixmult(m, r.origin);
	r2.direction = tmatrixmult(m, r.direction);
	return (r2);
}

void	set_transform(t_shape *s, float **t)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			s->transform[i][j] = t[i][j];
			j++;
		}
		i++;
	}
	free_matrix(t, 4);
	free_matrix(s->invtrans, 4);
	s->invtrans = minvert(s->transform, 4);
}


// TODO isinvertable check for minvert -- had sometimes segfault at these lines
t_ray	ray_for_pixel(t_camera *c, float px, float py)
{
	float	world_x;
	float	world_y;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;

	world_x = c->half_width - (px + 0.5) * c->pixel_size;
	world_y = c->half_height - (py + 0.5) * c->pixel_size;
	pixel = tmmultfree(minvert(c->transform, 4), point(world_x, world_y, -1));
	origin = tmmultfree(minvert(c->transform, 4), point(0, 0, 0));
//	pixel = tmatrixmult(minvert(c->transform, 4), point(world_x, world_y, -1));
//	origin = tmatrixmult(minvert(c->transform, 4), point(0, 0, 0));
	direction = tnorm(tsub(pixel, origin));
	return (ray(origin, direction));
}
