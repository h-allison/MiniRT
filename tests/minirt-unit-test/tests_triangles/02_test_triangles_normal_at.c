/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_test_triangles_normal_at.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/27 19:50:37 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangles_tests.h"

int	test_triangles_normal_at(void)
{
	t_shape	*t;
	t_tuple	n1;
	t_tuple	n2;
	t_tuple	n3;

	t = triangle(point(0, 1, 0), point(-1, 0, 0), point(1, 0, 0));
	n1 = t->local_normal_at(t, point(0, 0.5, 0));
	n2 = t->local_normal_at(t, point(-0.5, 0.75, 0));
	n3 = t->local_normal_at(t, point(0, 0.25, 0));
	if (!tisequal(n1, t->triangle->normal)
		|| !tisequal(n2, t->triangle->normal)
		|| !tisequal(n3, t->triangle->normal))
		return (-1);
	return (0);
}
