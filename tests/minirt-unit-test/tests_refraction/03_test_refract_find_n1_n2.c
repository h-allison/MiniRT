/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_test_refract_find_n1_n2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:02:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/23 02:58:50 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refraction_tests.h"

int test_refract_find_n1_n2(void)
{
	t_shape 		*sa;
	t_shape 		*sb;
	t_shape 		*sc;
	t_ray			r;
	t_intersection	*xs;
	t_comps			comps;

	sa = glass_sphere();
	set_transform(sa, scaling(2, 2, 2));
	sa->m->refractive_index = 1.5;
	sb = glass_sphere();
	set_transform(sb, translation(0, 0, -0.25));
	sb->m->refractive_index = 2;
	sc = glass_sphere();
	set_transform(sc, translation(0, 0, 0.25));
	sc->m->refractive_index = 2.5;
	r = ray(point(0, 0, -4), vector(0, 0, 1));
	xs = intersections(intersection(2, sa), intersection(2.75, sb));
	xs = intersections(intersection(3.25, sc), intersection(4.75, sb));
	xs = intersections(intersection(5.25, sc), intersection(6, sa));
	comps = prepare_computations(&xs[0], &r, xs);
	if (!fisequal(comps.n1, 1) || !fisequal(comps.n2, 1.5))
		return (-1);
	comps = prepare_computations(&xs[1], &r, xs);
	if (!fisequal(comps.n1, 1.5) || !fisequal(comps.n2, 2))
		return (-1);
	comps = prepare_computations(&xs[2], &r, xs);
	if (!fisequal(comps.n1, 2) || !fisequal(comps.n2, 2.5))
		return (-1);
	comps = prepare_computations(&xs[3], &r, xs);
	if (!fisequal(comps.n1, 2.5) || !fisequal(comps.n2, 2.5))
		return (-1);
	comps = prepare_computations(&xs[4], &r, xs);
	if (!fisequal(comps.n1, 2.5) || !fisequal(comps.n2, 1.5))
		return (-1);
	comps = prepare_computations(&xs[5], &r, xs);
	if (!fisequal(comps.n1, 1.5) || !fisequal(comps.n2, 1))
		return (-1);
	free_shape(sa);
	free_shape(sb);
	free_shape(sc);
	return (0);
}
