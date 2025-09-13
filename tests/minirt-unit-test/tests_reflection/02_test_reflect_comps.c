/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_test_reflect_comps.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:03:46 by hallison          #+#    #+#             */
/*   Updated: 2025/09/13 18:46:15 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection_tests.h"

int test_reflect_comps(void)
{
	t_shape			s;
	t_ray			r;
	t_intersection	i;
	t_comps			c;

	s = plane();
	r = ray(point(0, 1, -1), vector(0, -sqrtf(2)/2, sqrtf(2)/2));
	i = intersection(sqrtf(2), &s);
	c = prepare_computations(&i, &r);
	if (!fisequal(c.reflectv.x, 0) || !fisequal(c.reflectv.y, sqrtf(2)/2)
			|| !fisequal(c.reflectv.z, sqrtf(2)/2))
		return (-1);
	return (0);
}
