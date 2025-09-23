/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_groups_basic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:38:56 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/23 03:38:06 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "groups_tests.h"

int test_groups_basic(void)
{
	t_shape	*g;
	float	**idm;
	int		x;
	int		y;

	g = group();
	idm = create_id_matrix();
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (g->transform[y][x] != idm[y][x])
			return (-1);
			x++;
		}
		y++;
	}
	free_matrix(idm, 4);
	free_shape(g);
	return (0);
}
