/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_test_reflect_col_reflective.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:02:04 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/30 16:00:42 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "reflection_tests.h"

int test_reflect_col_reflective(void)
{
	t_world			*w;
	t_shape			*s;
	t_ray			r;
	t_intersection	i;
	t_comps			c;
	t_rgb			col;

	w = default_world();
	s = plane();
	s->m->reflective = 0.5;
	set_transform(s, translation(0, -1, 0));
	w->s[2] = s;
	w->s[3] = NULL;
	r = ray(point(0, 0, -3), vector(0, -sqrtf(2)/2, sqrtf(2)/2));
	i = intersection(sqrtf(2), s);
	c = prepare_computations(&i, &r, NULL);
	col = reflected_color(w, &c, 10);
	free_world(w);
	if (!fisequal(col.r, 0.190491) || !fisequal(col.g, 0.238114)
			|| !fisequal(col.b, 0.142868))
		return (-1);
	return (0);
}
