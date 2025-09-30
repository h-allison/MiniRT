/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:07:25 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/30 17:26:55 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	cube_uv_front(t_tuple point)
{
	t_tuple	uv;

	uv.x = fmod((point.x + 1), 2) / 2;
	uv.y = fmod((point.y + 1), 2) / 2;
	return (uv);
}

t_tuple	cube_uv_back(t_tuple point)
{
	t_tuple	uv;

	uv.x = fmod((1 - point.x), 2) / 2;
	uv.y = fmod((point.y + 1), 2) / 2;
	return (uv);
}

t_tuple	cube_uv_left(t_tuple point)
{
	t_tuple	uv;

	uv.x = fmod((point.z + 1), 2) / 2;
	uv.y = fmod((point.y + 1), 2) / 2;
	return (uv);
}

t_tuple	cube_uv_right(t_tuple point)
{
	t_tuple	uv;

	uv.x = fmod((1 - point.z), 2) / 2;
	uv.y = fmod((point.y + 1), 2) / 2;
	return (uv);
}
