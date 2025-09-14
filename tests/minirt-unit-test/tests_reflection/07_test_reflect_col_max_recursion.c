/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_test_reflect_col_max_recursion.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:01:53 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/14 12:14:42 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection_tests.h"

int test_reflect_col_max_recursion(void)
{
	t_world			w;
	t_shape			s;
	t_ray			r;
	t_intersection	i;
	t_comps			c;
	t_rgb			col;

	w = default_world();
	s = plane();
	s.m.reflective = 0.5;
	set_transform(&s, translation(0, -1, 0));
	s.invtrans = minvert(s.transform, 4);
	w.s[2] = s;
	w.s[3].transform = NULL;
	r = ray(point(0, 0, -3), vector(0, -sqrtf(2)/2, sqrtf(2)/2));
	i = intersection(sqrtf(2), &s);
	c = prepare_computations(&i, &r);
	col = reflected_color(&w, &c, 0);
	if (!fisequal(col.r, 0) || !fisequal(col.g, 0)
			|| !fisequal(col.b, 0))
		return (-1);
	return (0);
}
