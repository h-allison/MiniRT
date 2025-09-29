/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_triangles_create.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/27 19:43:42 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangles_tests.h"

int	test_triangles_create(void)
{
	t_shape	*t;
	t_tuple	p1;
	t_tuple	p2;
	t_tuple p3;

	p1 = point(0, 1, 0);
	p2 = point(-1, 0, 0);
	p3 = point(1, 0, 0);
	t = triangle(p1, p2, p3);
	if (!tisequal(t->triangle->p1, p1)
		|| !tisequal(t->triangle->p2, p2)
		|| !tisequal(t->triangle->p3, p3)
		|| !tisequal(t->triangle->e1, vector(-1, -1, 0))
		|| !tisequal(t->triangle->e2, vector(1, -1, 0))
		|| !tisequal(t->triangle->normal, vector(0, 0, -1)))
		return (-1);
	return (0);
}
