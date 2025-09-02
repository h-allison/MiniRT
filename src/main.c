/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:54:44 by hallison          #+#    #+#             */
/*   Updated: 2025/09/02 18:12:54 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mlx_handling(t_data *data);

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		rt_early_exit(ERROR_WRONG_ARGS);
	parse_file(argv[1], &data);
	printf("Time to raytrace!\n");
	mlx_handling(&data);
	exit(0);
}

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	render(void *param)
{
	static bool	render_done;
	t_data			*data;
	t_sphere		s;
	t_ray			r;
	t_tuple			ray_origin;
	t_tuple			position;
//	float			**m;
//	float			**m2;
	float			wall_z;
	float			wall_size;
	float			half;
	float			pixel_size;
	float			world_x;
	float			world_y;
	int				x;
	int				y;
	t_intersection	*t;
	t_intersection	*xs;

	data = (t_data *)param;
	if (!render_done)
	{
		ray_origin = point(0, 0, -5);
		s = sphere(point(0, 0, 0), color(0xFF, 0x00, 0));
//		m = scaling(0.5, 1, 1);
//		set_transform(&s, m);
//		free(m);
//		float shear[6] = {1, 0, 0, 0, 0, 0};
//		m = shearing(shear);
//		m2 = matrixmult(m, s.transform);
//		set_transform(&s, m2);
//		free(m);
//		free(m2);
		wall_z = 10;
		wall_size = 7;
		half = wall_size / 2;
		pixel_size = wall_size / WIN_WIDTH;
		y = 0;
		while (y < WIN_HEIGHT)
		{
			world_y = half - pixel_size * y;
			x = 0; 
			while (x < WIN_WIDTH)
			{
				world_x = -half + pixel_size * x;
				position = point(world_x, world_y, wall_z);
				r = ray(ray_origin, tnorm(tsub(position, ray_origin)));
				xs = intersect(s, r);
				t = hit(xs);
				if (t)
				{
					mlx_put_pixel(data->img, x, y, color_to_hex(t->object->color));
					free(t);
				}
				xs[0].object = NULL;
				x++;
			}
			y++;
		}
	}
	if (!render_done)
	{
		free(xs);
		free(s.transform );
		printf("render done!\n");
		canvas_export_ppm(data);
		render_done = true;
	}
}

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

int	mlx_handling(t_data *data)
{
	data->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, data->filename, true);
	if (!data->mlx)
		ft_error(); // TODO
	data->img = mlx_new_image(data->mlx, WIN_WIDTH,	WIN_HEIGHT);
	img_wipe(data, color(0x00, 0x00, 0x00));
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error(); // TODO
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
