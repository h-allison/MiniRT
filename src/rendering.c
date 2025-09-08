/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:54:44 by hallison          #+#    #+#             */
/*   Updated: 2025/09/09 01:40:28 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define CHUNK_SIZE 1

static int	render_chunk(t_camera *cam, t_world *world, mlx_image_t *img)
{
	static int  			y;
	int         			x;
	t_ray       			r;
	t_rgb       			col;

	x = 0;
	while (x < cam->hsize)
	{
		r = ray_for_pixel(cam, x, y);
		col = color_at(world, &r);
		mlx_put_pixel(img, x, y, color_to_hex(col));
		x++;
	}
	y++;
	if (y >= cam->vsize)
		return (2);
	return (1);
}

void    render(void *param)
{
	static int		status;
	static t_camera cam;
	static t_world  world;
	t_data          *data;
	int				i;

	if (status == 0)
	{
		data = (t_data *)param;
		world = default_world_2();
		cam = camera(WIN_WIDTH, WIN_HEIGHT, M_PI / 3);
		cam.transform = view_transform(point(0, 1.5, -5),
				point(0, 1, 0), vector(0, 1, 0));
		status = 1;
	}
	if (status == 1)
		status = render_chunk(&cam, &world, data->img);
	if (status == 2)
	{
		printf("render done!\n");
		free_matrix(cam.transform, 4);
		free(world.light);
		i = 0;
		while (world.s[i].transform)
			free_matrix(world.s[i++].transform, 4);
		free(world.s);
		canvas_export_ppm(data);
		status = 3;
		// mlx_loop_hook(data->mlx, NULL, NULL);
	}
}
