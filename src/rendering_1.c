/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 11:26:02 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/02 12:53:22 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	img_wipe(t_data *data, t_rgb color)
{
	int		y;
	int		x;

	y = 0;
	x = 0;
	while (y < data->mlx->height)
	{
		x = 0;
		while (x < data->mlx->width)
		{
			mlx_put_pixel(data->img, x, y, color_to_hex(color));
			x++;
		}
		y++;
	}
	return ;
}

void	render_with_parsing(void *param)
{
	render_chunk(((t_data *)param)->world, param);
}

void	render(void *param)
{
	static int		render_status;
	static t_world	*world;
	static t_camera	*cam;
	static t_data	*data;

	if (render_status == 0)
	{
		data = (t_data *)param;
		world = default_world_cyl();
		cam = camera(WIN_WIDTH, WIN_HEIGHT, M_PI / 3);
		cam->transform = view_transform(point(-3, 2, -6),
				point(0, 1, 0), vector(0, 1, 0));
		data->reset = true;
		data->cam = cam;
		render_status = 1;
	}
	if (render_status == 1)
		render_status = render_chunk(world, data);
}
