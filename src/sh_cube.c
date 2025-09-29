/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 17:49:31 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 20:41:37 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*cube(void)
{
	t_shape	*s;

	s = malloc(sizeof(t_shape));
	s->parent = NULL;
	s->group = NULL;
	s->triangle = NULL;
	s->transform = create_id_matrix();
	s->invtrans = minvert(s->transform, 4);
	s->local_normal_at = local_normal_at_cube;
	s->local_intersect = local_intersect_cube;
	s->m = material();
	return (s);
}

t_tuple	local_normal_at_cube(t_shape *s, t_tuple local_point)
{
	float	maxc;

	(void)s;
	maxc = maxf(fabs(local_point.x), fabs(local_point.y), fabs(local_point.z));
	if (maxc == fabs(local_point.x))
		return (vector(local_point.x, 0, 0));
	if (maxc == fabs(local_point.y))
		return (vector(0, local_point.y, 0));
	return (vector(0, 0, local_point.z));
}

static void	check_axis(float *tmin, float *tmax, float origin, float direction)
{
	float	tmin_numerator;
	float	tmax_numerator;

	tmin_numerator = (-1 - origin);
	tmax_numerator = (1 - origin);
	if (fabs(direction) >= EPSILON)
	{
		*tmin = tmin_numerator / direction;
		*tmax = tmax_numerator / direction;
	}
	else
	{
		*tmin = tmin_numerator * FLT_MAX;
		*tmax = tmax_numerator * FLT_MAX;
	}
	if (*tmin > *tmax)
		swapf(tmin, tmax);
	return ;
}

t_intersection	*local_intersect_cube(t_shape *s, t_ray r)
{
	t_tminmax	t;
	float		tmin;
	float		tmax;

	check_axis(&t.xtmin, &t.xtmax, r.origin.x, r.direction.x);
	check_axis(&t.ytmin, &t.ytmax, r.origin.y, r.direction.y);
	check_axis(&t.ztmin, &t.ztmax, r.origin.z, r.direction.z);
	tmin = maxf(t.xtmin, t.ytmin, t.ztmin);
	tmax = minf(t.xtmax, t.ytmax, t.ztmax);
	if (tmin > tmax)
		return (intersections(intersection(0, NULL), intersection(0, NULL)));
	return (intersections(intersection(tmin, s), intersection(tmax, s)));
}
