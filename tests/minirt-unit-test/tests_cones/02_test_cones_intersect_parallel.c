/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_test_cones_intersect_parallel.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/22 15:49:52 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cones_tests.h"

int test_cones_intersect_parallel(void)
{
	t_shape			c;
	t_ray			r;
	t_intersection	*xs;

	c = cone();
	
	r = ray(point(0, 0, -1), tnorm(vector(0, 1, 1)));
	xs = local_intersect_cone(&c, r);
	if (!fisequal(xs[0].t, 0.35355) || !fisequal(xs[1].t, 0))
		return (-1);
	xs[0].object = NULL;
	free_shape(&c);
	return (0);
}
