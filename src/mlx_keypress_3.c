/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keypress_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:20:16 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/30 20:56:38 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	keypress_s(t_data *data)
{
	data->cam->transform = mmultfree(rotation_x(-0.5 * DEG2RAD),
			data->cam->transform);
	camera_update_cache(data->cam);
	mark_moving(data);
}

void	keypress_w(t_data *data)
{
	data->cam->transform = mmultfree(rotation_x(0.5 * DEG2RAD),
			data->cam->transform);
	camera_update_cache(data->cam);
	mark_moving(data);
}

void	keypress_a(t_data *data)
{
	data->cam->transform = mmultfree(rotation_y(1 * DEG2RAD),
			data->cam->transform);
	camera_update_cache(data->cam);
	mark_moving(data);
}

void	keypress_d(t_data *data)
{
	data->cam->transform = mmultfree(rotation_y(-1 * DEG2RAD),
			data->cam->transform);
	camera_update_cache(data->cam);
	mark_moving(data);
}
