/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_test_triangles_ray_misses_p1-p2-p3.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/27 20:42:42 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangles_tests.h"

int	test_triangles_ray_misses_p1_p2_p3(void)
{
	t_shape			*t;
	t_ray			r;
	t_intersection	*xs;

	t = triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0));
	r = ray(point(-1, 1, -2), vector(0, 0, 1));
	xs = t->local_intersect(t, r);
	if (xs[0].object || !fisequal(xs[0].t, 0))
		return (-1);
	xs[0].object = NULL;
	r = ray(point(0, -1, -2), vector(0, 0, 1));
	xs = t->local_intersect(t, r);
	if (xs[0].object || !fisequal(xs[0].t, 0))
		return (-1);
	return (0);
}
