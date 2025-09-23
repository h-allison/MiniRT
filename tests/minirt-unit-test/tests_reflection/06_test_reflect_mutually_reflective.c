/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_test_reflect_mutually_reflective.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:01:53 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/23 02:55:03 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection_tests.h"

int test_reflect_mutually_reflective(void)
{
	t_world			w;
	t_shape			*lower;
	t_shape			*upper;
	t_ray			r;
	t_rgb			col;

	w = default_world();
	w.light[0] = point_light(point(0, 0, 0), color(255, 255, 255));
	lower = plane();
	lower->m->reflective = 1;
	set_transform(lower, translation(0, -1, 0));
	lower->invtrans = minvert(lower->transform, 4);
	w.s[0] = lower;
	upper = plane();
	upper->m->reflective = 1;
	set_transform(upper, translation(0, 1, 0));
	upper->invtrans = minvert(upper->transform, 4);
	w.s[1] = upper;
	w.s[2] = NULL;
	r = ray(point(0, 0, 0), vector(0, 1, 0));
	col = color_at(&w, &r, 10);
	return (0);
}
