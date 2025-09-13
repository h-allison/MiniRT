/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_test_reflect_shade_hit_reflective.c             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:03:46 by hallison          #+#    #+#             */
/*   Updated: 2025/09/13 21:49:48 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection_tests.h"

int test_reflect_shade_hit_reflective(void)
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
	col = shade_hit(&w, &c);
	printf("   %f %f %f   ",col.r, col.g, col.b);
	if (!fisequal(col.r, 0.876886) || !fisequal(col.g, 0.924509)
			|| !fisequal(col.b, 0.829263))
		return (-1);
	return (0);
}
