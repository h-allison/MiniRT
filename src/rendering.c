/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:54:44 by hallison          #+#    #+#             */
/*   Updated: 2025/09/08 17:13:17 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	render(void *param)
{
	static bool		render_done;
	t_data			*data;
	t_camera		cam;
	t_world			world;

	if (!render_done)
	{
		data = (t_data *)param;
		world = default_world_2();
		cam = camera(WIN_WIDTH, WIN_HEIGHT, M_PI / 3);
		cam.transform = view_transform(point(0, 1.5, -5),
				point(0, 1, 0), point(0, 1, 0));
		render_loop(&cam, &world, data->img);
		printf("render done!\n");
		canvas_export_ppm(data);
		render_done = true;
	}
	usleep(1000);
}

void	render_loop(t_camera *cam, t_world *world, mlx_image_t *img)
{
		int		x;
		int		y;
		t_ray	r;
		t_rgb	col;

		y = 0;
		while (y < cam->vsize)
		{
			x = 0; 
			while (x < cam->hsize)
			{
				r = ray_for_pixel(cam, x, y);
				col = color_at(world, &r);
				mlx_put_pixel(img, x, y, color_to_hex(col));
				x++;
			}
			y++;
		}
}
