/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_test_pattern.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:16:28 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/25 02:32:33 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"

int test_pattern_gen_basic(void)
{
	t_pattern	*pat;
	int			x;
	int			y;
	float		**idm;

	idm = create_id_matrix();
	pat = create_test_pattern();
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (!fisequal(pat->transform[y][x], idm[y][x]))
			{
				free_matrix(idm, 4);
				free_pattern(pat);
				return (-1);
			}
			x++;
		}
		y++;
	}
	free_matrix(idm, 4);
	free_pattern(pat);
	return (0);
}
