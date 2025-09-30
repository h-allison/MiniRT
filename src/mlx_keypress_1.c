/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_keypress_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 20:20:16 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/30 20:57:11 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	keypress_escape(t_data *data)
{
	mlx_delete_image(data->mlx, data->img);
	mlx_close_window(data->mlx);
	free_world(data->world);
	free_cam(data->cam);
}

void	keypress_up(t_data *data)
{
	data->cam->transform = mmultfree(translation(0, 0, 0.05),
			data->cam->transform);
	data->reset = true;
}

void	keypress_down(t_data *data)
{
	data->cam->transform = mmultfree(translation(0, 0, -0.05),
			data->cam->transform);
	data->reset = true;
}

void	keypress_left(t_data *data)
{
	data->cam->transform = mmultfree(translation(-0.1, 0, 0),
			data->cam->transform);
	data->reset = true;
}

void	keypress_right(t_data *data)
{
	data->cam->transform = mmultfree(translation(0.1, 0, 0),
			data->cam->transform);
	data->reset = true;
}
