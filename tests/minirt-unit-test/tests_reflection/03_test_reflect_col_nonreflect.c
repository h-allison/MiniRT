/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_test_reflect_col_nonreflect.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:02:20 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/14 12:11:55 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection_tests.h"

int test_reflect_col_nonreflect(void)
{
	t_world			w;
	t_ray			r;
	t_intersection	i;
	t_comps			c;
	t_rgb			col;

	w = default_world();
	r = ray(point(0, 1, -1), vector(0, -sqrtf(2)/2, sqrtf(2)/2));
	w.s[1].m.ambient = 1;
	i = intersection(1, &w.s[1]);
	c = prepare_computations(&i, &r);
	col = reflected_color(&w, &c, 10);
	if (!fisequal(col.r, 0) || !fisequal(col.g, 0)
			|| !fisequal(col.b, 0))
		return (-1);
	return (0);
}
