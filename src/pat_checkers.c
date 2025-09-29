/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pat_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:58:07 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 20:32:58 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	*checkers_pattern(t_rgb a, t_rgb b)
{
	t_pattern	*checkers;

	checkers = malloc(sizeof(t_pattern));
	checkers->a = a;
	checkers->b = b;
	checkers->transform = create_id_matrix();
	checkers->invtrans = minvert(checkers->transform, 4);
	checkers->pattern_at = checkers_at;
	checkers->uv_pattern = NULL;
	checkers->canvas = NULL;
	checkers->status = true;
	return (checkers);
}

t_rgb	checkers_at(t_pattern *checkers, t_tuple point)
{
	if ((int)(floorf(point.x) + floorf(point.y) + floorf(point.z)) % 2 == 0)
		return (checkers->a);
	return (checkers->b);
}
