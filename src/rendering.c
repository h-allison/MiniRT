/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:54:44 by hallison          #+#    #+#             */
/*   Updated: 2025/09/18 17:32:28 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define CHUNK_SIZE 1

static int	render_chunk(t_world *world, t_data *data)
{
	static int	y;
	int			x;
	t_ray		r;
	t_rgb		col;

	if (data->reset)
	{
		y = 0;
		data->reset = false;
	}
	if (y >= data->cam->vsize)
		return (1);
	x = 0;
	while (x < data->cam->hsize)
	{
		r = ray_for_pixel(data->cam, x, y);
		col = color_at(world, &r, MAX_RECURSION);
		mlx_put_pixel(data->img, x, y, color_to_hex(col));
		x++;
	}
	y++;
	return (1);
}

void	render(void *param)
{
	static int		render_status;
//	int				i;
	static t_world	world;
	static t_camera	cam;
	static t_data	*data;

	if (render_status == 0)
	{
		data = (t_data *)param;
		world = default_world_cyl();
		cam = camera(WIN_WIDTH, WIN_HEIGHT, M_PI / 3);
		cam.transform = view_transform(point(-2, 2, -6),
			point(0, 1, 0), vector(0, 1, 0));
		data->reset = true;
		data->cam = &cam;
		render_status = 1;
	}
	if (render_status == 1)
	{
		render_status = render_chunk(&world, data);
	}
	if (render_status == 2)
	{
//		free_matrix(cam.transform, 4);
//		free(world.light);
//		i = 0;
//		while (world.s[i].transform)
//			free_matrix(world.s[i++].transform, 4);
//		free(world.s);
//		canvas_export_ppm(data);
		render_status = 3;
		// mlx_loop_hook(data->mlx, NULL, NULL);
	}
}
