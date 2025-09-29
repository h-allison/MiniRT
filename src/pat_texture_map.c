/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pat_texture_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:58:07 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/29 19:09:48 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	*texture_map(t_pattern *uv_pattern, t_tuple (*map)(t_tuple))
{
	t_pattern	*pattern;

	pattern = malloc(sizeof(t_pattern));
	pattern->transform = create_id_matrix();
	pattern->invtrans = minvert(pattern->transform, 4);
	pattern->pattern_at = texture_at;
	pattern->uv_pattern = uv_pattern;
	pattern->map = map;
	pattern->canvas = NULL;
	pattern->status = true;
	return (pattern);
}

t_rgb	texture_at(t_pattern *texture_map, t_tuple point)
{
	t_tuple	uv;
	
	uv = texture_map->map(point);
	return (texture_map->uv_pattern->pattern_at(texture_map->uv_pattern, uv));
}
