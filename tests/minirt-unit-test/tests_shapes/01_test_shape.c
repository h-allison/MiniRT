/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:03:46 by hallison          #+#    #+#             */
/*   Updated: 2025/09/12 11:57:14 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes_tests.h"

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

int test_shape_basic(void)
{
	t_shape	s;
	int			x;
	int			y;
	float		**idm;

	s = create_test_shape();
	idm = create_id_matrix();
	y = 0;
	while(y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (!fisequal(s.transform[y][x], idm[y][x]))
			{
				free_matrix(idm, 4);
				return(free_matrices_and_return(&s, -1));
			}
			x++;
		}
		y++;
	}
	free_matrix(idm, 4);
	return(free_matrices_and_return(&s, 0));
}
