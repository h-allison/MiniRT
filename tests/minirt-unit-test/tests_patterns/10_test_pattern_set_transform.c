/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_test_pattern_set_transform.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:16:12 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/23 02:40:46 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"

int test_pattern_set_transform(void)
{
	t_pattern	*pat;
	int			x;
	int			y;
	float		**m;

	pat = create_test_pattern();
	set_pattern_transform(pat, translation(1, 2, 3));
	m = translation(1, 2, 3);
	y = 0;
	while (y < 4)
	{
		x = 0;
		while (x < 4)
		{
			if (!fisequal(pat->transform[y][x], m[y][x]))
			{
				free_matrix(m, 4);
				free_matrix(pat->transform, 4);
				return (-1);
			}
			x++;
		}
		y++;
	}
	free_matrix(m, 4);
	free_matrix(pat->transform, 4);
	return (0);
}
