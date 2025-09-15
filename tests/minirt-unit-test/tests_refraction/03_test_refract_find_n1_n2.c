/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_test_refract_find_n1_n2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:02:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/15 12:39:18 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refraction_tests.h"

int test_refract_find_n1_n2(void)
{
	t_shape 		sa;
	t_shape 		sb;
	t_shape 		sc;
	t_ray			r;
	t_intersection	*xs;
	t_comp			comps;
	int				i;

	sa = glass_sphere();
	s.transform = set_transform(scaling(2, 2, 2));
	s.m.refractive_index = 1.5;
	sb = glass_sphere();
	s.transform = set_transform(translation(0, 0, -0.25));
	s.m.refractive_index = 2;
	sc = glass_sphere();
	s.transform = set_transform(translation(0, 0, 0.25));
	s.m.refractive_index = 2.5;
	r = ray(point(0, 0, -4), vector(0, 0, 1));
	xs = intersections(2, sa);
	xs = intersections(2.75, sb);
	xs = intersections(3.25, sc);
	xs = intersections(4.75, sb);
	xs = intersections(5.25, sc);
	xs = intersections(6, sa);
	i = 0;
	while (i < 6)
	{
		comps = prepare_computations(xs[i], r, xs);
		printf("%i | %f | %f", i, comps.n1, comps.ns);
		i++;
	}
	return (0);
}
