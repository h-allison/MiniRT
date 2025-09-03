/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 17:55:04 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/03 13:20:23 by mmillhof         ###   ########.fr       */
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

// TODO malloc free and exit

t_ray	transform(t_ray r, float **m)
{
	t_ray	r2;

	r2.origin = tmatrixmult(m, r.origin);
	r2.direction = tmatrixmult(m, r.direction);
	return (r2);
}

/* For now, just for spheres*/

void	set_transform(t_sphere *s, float **t)
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
}
