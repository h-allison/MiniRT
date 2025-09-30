/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 00:07:25 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/30 17:26:41 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	cube_uv_up(t_tuple point)
{
	t_tuple	uv;

	uv.x = fmod((point.x + 1), 2) / 2;
	uv.y = fmod((1 - point.z), 2) / 2;
	return (uv);
}

t_tuple	cube_uv_down(t_tuple point)
{
	t_tuple	uv;

	uv.x = fmod((point.x + 1), 2) / 2;
	uv.y = fmod((point.z + 1), 2) / 2;
	return (uv);
}
