/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pat_uv_align_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:58:07 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/02 17:12:21 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	uv_align_check_at(t_pattern *align_check, t_tuple uv)
{
	if (uv.y > 0.8)
	{
		if (uv.x < 0.2)
			return (align_check->ul);
		if (uv.x > 0.8)
			return (align_check->ur);
	}
	else if (uv.y < 0.2)
	{
		if (uv.x < 0.2)
			return (align_check->bl);
		if (uv.x > 0.8)
			return (align_check->br);
	}
	return (align_check->main);
}

t_pattern	*uv_align_check(t_rgb main, t_rgb ul, t_rgb ur, t_rgb bl, t_rgb br)
{
	t_pattern	*align_check;

	align_check = malloc(sizeof(t_pattern));
	align_check->main = main;
	align_check->ul = ul;
	align_check->ur = ur;
	align_check->bl = bl;
	align_check->br = br;
	align_check->transform = create_id_matrix();
	align_check->invtrans = minvert(align_check->transform, 4);
	align_check->pattern_at = uv_align_check_at;
	align_check->uv_pattern = NULL;
	align_check->canvas = NULL;
	align_check->status = true;
	return (align_check);
}
