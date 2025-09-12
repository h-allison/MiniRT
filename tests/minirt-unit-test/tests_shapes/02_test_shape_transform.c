/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_test_shape_transform.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:22:10 by hallison          #+#    #+#             */
/*   Updated: 2025/09/12 11:59:22 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes_tests.h"

// Tests that transforms can be applied to shapes

static int	free_matrices_and_return(t_shape *p, int ret)
{
	if (p->transform)
		free_matrix(p->transform, 4);
	if (p->invtrans)
		free_matrix(p->invtrans, 4);
	if (p->m.pattern.transform)
		free_matrix(p->m.pattern.transform, 4);
	if (p->m.pattern.invtrans)
		free_matrix(p->m.pattern.invtrans, 4);
	return (ret);
}

int test_shape_transform(void)
{
	t_shape	s;
	int			x;
	int			y;
	float		**tm;

	s = create_test_shape();
	set_transform(&s, translation(2, 3, 4));
	tm = translation(2, 3, 4);
	y = 0;
	while(y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (!fisequal(s.transform[y][x], tm[y][x]))
			{
				free_matrix(tm, 4);
				return(free_matrices_and_return(&s, -1));
			}
			x++;
		}
		y++;
	}
	free_matrix(tm, 4);
	return(free_matrices_and_return(&s, 0));
}
