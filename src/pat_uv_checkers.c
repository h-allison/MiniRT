/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pat_uv_checkers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:58:07 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 20:36:31 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	*uv_checkers(float width, float height, t_rgb a, t_rgb b)
{
	t_pattern	*checkers;

	checkers = malloc(sizeof(t_pattern));
	checkers->a = a;
	checkers->b = b;
	checkers->width = width;
	checkers->height = height;
	checkers->transform = create_id_matrix();
	checkers->invtrans = minvert(checkers->transform, 4);
	checkers->pattern_at = uv_checkers_at;
	checkers->uv_pattern = NULL;
	checkers->canvas = NULL;
	checkers->status = true;
	return (checkers);
}

t_rgb	uv_checkers_at(t_pattern *checkers, t_tuple uv)
{
	float	u2;
	float	v2;

	u2 = floorf(uv.x * checkers->width);
	v2 = floorf(uv.y * checkers->height);
	if (fmod(u2 + v2, 2) == 0)
		return (checkers->a);
	return (checkers->b);
}
