/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_test_cyls_intersecting_caps.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:55:01 by hallison          #+#    #+#             */
/*   Updated: 2025/09/23 03:34:48 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_cyl_tests.h"

void	debug_print_xs(t_intersection *xs)
{
	int	i = 0;
	printf("\n");
	while(xs[i].object != NULL)
	{
		printf("xs[%d].obj = %p	.t = %f\n", i, xs[i].object, xs[i].t);
		i++;
	}
	printf("\n");
}

int test_cyls_intersecting_caps(void)
{
    t_shape         *c;
	t_ray			r;
    t_intersection  *xs;

    c = cylinder();
 	c->minimum = 1;
	c->maximum = 2;
	c->closed = true;
	r = ray(point(0, 3, 0), tnorm(vector(0, -1, 0)));
    
	xs = local_intersect_cyl(c, r);
	if (!xs || !xs[0].object || !xs[1].object || xs[2].object)
        return (-1);
    xs[0].object = NULL;

	c->saved_ray = ray(point(0, 3, -2), tnorm(vector(0, -1, 2)));
    xs = local_intersect_cyl(c, r);
	if (!xs || !xs[0].object || !xs[1].object || xs[2].object)
        return (-1);
    xs[0].object = NULL;
	
	c->saved_ray = ray(point(0, 4, -2), tnorm(vector(0, -1, 1)));
    xs = local_intersect_cyl(c, r);
    if (!xs || !xs[0].object || !xs[1].object || xs[2].object)
        return (-1);
    xs[0].object = NULL;

	c->saved_ray = ray(point(0, 0, -2), tnorm(vector(0, 1, 2)));
    xs = local_intersect_cyl(c, r);
    if (!xs || !xs[0].object || !xs[1].object || xs[2].object)
        return (-1);
    xs[0].object = NULL;
	
	c->saved_ray = ray(point(0, -1, -2), tnorm(vector(0, 1, 1)));
    xs = local_intersect_cyl(c, r);
    if (!xs || !xs[0].object || !xs[1].object || xs[2].object)
        return (-1);
    xs[0].object = NULL;
	free_shape(c);
	return (0);
}
