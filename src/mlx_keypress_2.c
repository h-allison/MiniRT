/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keypress_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:20:16 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/30 20:56:55 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	keypress_r(t_data *data)
{
	data->cam->transform = mmultfree(translation(0, -0.05, 0),
			data->cam->transform);
	camera_update_cache(data->cam);
	mark_moving(data);
}

void	keypress_f(t_data *data)
{
	data->cam->transform = mmultfree(translation(0, 0.05, 0),
			data->cam->transform);
	camera_update_cache(data->cam);
	mark_moving(data);
}

void	keypress_q(t_data *data)
{
	data->cam->transform = mmultfree(rotation_z(-0.5 * DEG2RAD),
			data->cam->transform);
	camera_update_cache(data->cam);
	mark_moving(data);
}

void	keypress_e(t_data *data)
{
	data->cam->transform = mmultfree(rotation_z(0.5 * DEG2RAD),
			data->cam->transform);
	camera_update_cache(data->cam);
	mark_moving(data);
}

void	keypress_p(t_data *data)
{
	printf("EXPORTING...\n");
	canvas_export_ppm(data);
	printf("done!\n");
}
