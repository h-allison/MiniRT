/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_test_cyls_intersect_constrained.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:12:11 by hallison          #+#    #+#             */
/*   Updated: 2025/09/21 04:08:13 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub_cyl_tests.h"

int test_cyls_intersect_constrained(void)
{
    t_shape         c;
    t_intersection  *xs;

    c = cylinder();
 	c.minimum = 1;
	c.maximum = 2;
	c.saved_ray = ray(point(0, 1.5, 0), tnorm(vector(0.1, 1, 0)));
    xs = local_intersect_cyl(&c);
    if (!(xs && xs[0].t == 0 && !xs[0].object))
        return (-1);
    xs[0].object = NULL;
	
	c.saved_ray = ray(point(0, 3, -5), tnorm(vector(0, 0, 1)));
    xs = local_intersect_cyl(&c);
    if (!(xs && xs[0].t == 0 && !xs[0].object))
        return (-1);
    xs[0].object = NULL;
	
	c.saved_ray = ray(point(0, 0, -5), tnorm(vector(0, 0, 1)));
    xs = local_intersect_cyl(&c);
    if (!(xs && xs[0].t == 0 && !xs[0].object))
        return (-1);
    xs[0].object = NULL;
	
	c.saved_ray = ray(point(0, 2, -5), tnorm(vector(0, 0, 1)));
    xs = local_intersect_cyl(&c);
    if (!(xs && xs[0].t == 0 && !xs[0].object))
        return (-1);
    xs[0].object = NULL;
	
	c.saved_ray = ray(point(0, 1, -5), tnorm(vector(0, 0, 1)));
    xs = local_intersect_cyl(&c);
    if (!(xs && xs[0].t == 0 && !xs[0].object))
        return (-1);
    xs[0].object = NULL;
	
	c.saved_ray = ray(point(0, 1.5, -2), tnorm(vector(0, 0, 1)));
    xs = local_intersect_cyl(&c);
    if (!xs || !xs[0].object || !xs[1].object)
        return (-1);
    xs[0].object = NULL;
	free_shape(&c);
	return (0);
}
