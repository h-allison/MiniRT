/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_test_cones_intersect_parallel.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/18 11:34:18 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cones_tests.h"

int test_cones_intersect_parallel(void)
{
	t_shape			c;
	t_intersection	*xs;

	c = cone();
	
	c.saved_ray = ray(point(0, 0, -1), tnorm(vector(0, 1, 1)));
	xs = local_intersect_cone(&c);
	if (!fisequal(xs[0].t, 0.35355) || !fisequal(xs[1].t, 0))
		return (-1);
	xs[0].object = NULL;
	return (0);
}
