/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:07:25 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 19:13:17 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* ABSTRACT FUNCTION */

t_rgb	pattern_at_shape(t_pattern *pat, t_shape *shape, t_tuple world_point)
{
	t_tuple	shape_point;
	t_tuple	pattern_point;

	shape_point = world_to_object(shape, world_point);
	pattern_point = tmatrixmult(pat->invtrans, shape_point);
	return (pat->pattern_at(pat, pattern_point));
}

/* PATTERN HELPER */

void	set_pattern_transform(t_pattern *pat, float **t)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			pat->transform[i][j] = t[i][j];
			j++;
		}
		i++;
	}
	free_matrix(t, 4);
	free_matrix(pat->invtrans, 4);
	pat->invtrans = minvert(pat->transform, 4);
}
