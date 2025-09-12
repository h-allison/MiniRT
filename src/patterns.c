/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:07:25 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/12 21:22:10 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	stripe_pattern(t_rgb a, t_rgb b)
{
	t_pattern	pat;

	pat.a = a;
	pat.b = b;
	pat.transform = create_id_matrix();
	pat.invtrans = minvert(pat.transform, 4);
	pat.status = true;
	return (pat);
}

t_rgb	stripe_at(t_pattern *pat, t_tuple point)
{
	int	pint;

	pint = (int)floorf(point.x);
	if (pint % 2 == 0)
		return (pat->a);
	return (pat->b);
}

t_rgb	stripe_at_object(t_pattern *pat, t_shape *object, t_tuple point)
{
	t_tuple	object_point;
	t_tuple pattern_point;

	object_point = tmatrixmult(object->invtrans, point);
	pattern_point = tmatrixmult(pat->invtrans, object_point);
	return (stripe_at(pat, pattern_point));
}

t_rgb	pattern_at(t_pattern *pat, t_tuple point)
{
	t_rgb	col;

	(void) pat;
	col.r = point.x;
	col.g = point.y;
	col.b = point.z;
	return (col);
}

t_rgb	pattern_at_shape(t_pattern *pat, t_shape *shape, t_tuple point)
{
	t_tuple	shape_point;
	t_tuple pattern_point;

	shape_point = tmatrixmult(shape->invtrans, point);
	pattern_point = tmatrixmult(pat->invtrans, shape_point);
	return (pattern_at(pat, pattern_point));
}

void	set_pattern_transform(t_pattern *pat, float **t)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			pat->transform[i][j] = t[i][j];
			j++;
		}
		i++;
	}
	free_matrix(t, 4);
	pat->invtrans = minvert(pat->transform, 4);
}
