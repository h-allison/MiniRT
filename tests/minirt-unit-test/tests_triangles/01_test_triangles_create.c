/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_triangles_create.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/27 17:48:44 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "triangles_tests.h"

int	test_triangles_create(void)
{
	t_tri	*t;
	t_tuple	p1;
	t_tuple	p2;
	t_tuple p3;

	p1 = point(0, 1, 0);
	p2 = point(-1, 0, 0);
	p3 = point(1, 0, 0);
	t = triangle(p1, p2, p3);
	if (!tisequal(t->p1, p1)
		|| !tisequal(t->p2, p2)
		|| !tisequal(t->p3, p3)
		|| !tisequal(t->e1, vector(-1, -1, 0))
		|| !tisequal(t->e2, vector(1, -1, 0))
		|| !tisequal(t->normal, vector(0, 0, -1)))
		return (-1);
	return (0);
}
