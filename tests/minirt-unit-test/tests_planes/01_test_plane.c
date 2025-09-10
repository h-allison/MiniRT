/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:09:48 by hallison          #+#    #+#             */
/*   Updated: 2025/09/10 13:37:20 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "planes_tests.h"

bool	tuples_are_equal(t_tuple *t1, t_tuple t2)
{
	if (!fisequal(t1->x, t2.x))
		return(false);
	if (!fisequal(t1->y, t2.y))
		return(false);
	if (!fisequal(t1->z, t2.z))
		return(false);
	if (!fisequal(t1->w, t2.w))
		return(false);
	return(true);
}

int	mfree_fail(float **tm)
{
	free_matrix(tm, 4);
	return (-1);
}

int test_plane(void)
{
	t_shape		p;
	t_tuple		n1;
	t_tuple		n2;
	t_tuple		n3;

	p = plane();
	n1 = normal_at(&p, point(0, 0, 0));
	n2 = normal_at(&p, point(10, 0, -10));
	n3 = normal_at(&p, point(-5, 0, 150));

	if (!tuples_are_equal(&n1, vector(0, 1, 0)))
		return(mfree_fail(p.transform));
	if (!tuples_are_equal(&n2, vector(0, 1, 0)))
		return(mfree_fail(p.transform));
	if (!tuples_are_equal(&n3, vector(0, 1, 0)))
		return(mfree_fail(p.transform));
	free_matrix(p.transform, 4);
	return (0);
}
