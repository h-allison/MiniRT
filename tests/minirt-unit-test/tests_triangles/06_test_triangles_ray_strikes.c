/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_test_triangles_ray_strikes.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/27 20:58:45 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangles_tests.h"

int	test_triangles_ray_strikes(void)
{
	t_shape			*t;
	t_ray			r;
	t_intersection	*xs;

	t = triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0));
	r = ray(point(0, 0.5, -2), vector(0, 0, 1));
	xs = t->local_intersect(t, r);
	if (!fisequal(xs[0].t, 2))
		return (-1);
	return (0);
}
