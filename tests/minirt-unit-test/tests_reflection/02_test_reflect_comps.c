/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_test_reflect_comps.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:02:40 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/25 18:43:45 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection_tests.h"

int test_reflect_comps(void)
{
	t_shape			*s;
	t_ray			r;
	t_intersection	i;
	t_comps			c;

	s = plane();
	r = ray(point(0, 1, -1), vector(0, -sqrtf(2)/2, sqrtf(2)/2));
	i = intersection(sqrtf(2), s);
	c = prepare_computations(&i, &r, NULL);
	free_shape(s);
	if (!fisequal(c.reflectv.x, 0) || !fisequal(c.reflectv.y, sqrtf(2)/2)
			|| !fisequal(c.reflectv.z, sqrtf(2)/2))
		return (-1);
	return (0);
}
