/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pat_tests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:12:15 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 20:33:26 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* TEST PATTERN */

t_pattern	*create_test_pattern(void)
{
	t_pattern	*pat;

	pat = malloc(sizeof(t_pattern));
	pat->a = color(255, 255, 255);
	pat->b = color(0, 0, 0);
	pat->transform = create_id_matrix();
	pat->invtrans = minvert(pat->transform, 4);
	pat->pattern_at = &pattern_at;
	pat->uv_pattern = NULL;
	pat->canvas = NULL;
	pat->status = true;
	return (pat);
}

/* OLD FUNCTIONS */

t_rgb	stripe_at_object(t_pattern *pat, t_shape *object, t_tuple world_point)
{
	t_tuple	object_point;
	t_tuple	pattern_point;

	object_point = tmatrixmult(object->invtrans, world_point);
	pattern_point = tmatrixmult(pat->invtrans, object_point);
	return (stripe_at(pat, pattern_point));
}

/* TEST FUNCTION */

t_rgb	pattern_at(t_pattern *pat, t_tuple point)
{
	t_rgb	col;

	(void) pat;
	col.r = point.x;
	col.g = point.y;
	col.b = point.z;
	return (col);
}

/* PART OF TEST PATTERNS 14 */

char	*face_from_point(t_tuple point)
{
	float	abs_x;
	float	abs_y;
	float	abs_z;
	float	coord;

	abs_x = fabs(point.x);
	abs_y = fabs(point.y);
	abs_z = fabs(point.z);
	coord = maxf(abs_x, abs_y, abs_z);
	if (coord == point.x)
		return ("right");
	if (coord == -point.x)
		return ("left");
	if (coord == point.y)
		return ("up");
	if (coord == -point.y)
		return ("down");
	if (coord == point.z)
		return ("front");
	return ("back");
}
