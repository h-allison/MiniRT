/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:54:44 by hallison          #+#    #+#             */
/*   Updated: 2025/09/04 17:48:03 by hallison         ###   ########.fr       */
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
	return (0);
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
	t_object		s;
	t_ray			r;
	t_rgb			col;
	t_tuple			ray_origin;
	t_tuple			pos;
	t_largs			largs;
	float			wall_z;
	float			wall_size;
	float			half;
	float			pixel_size;
	float			world_x;
	float			world_y;
	int				x;
	int				y;
	t_intersection	*ht;
	t_intersection	*xs;

	data = (t_data *)param;
	if (!render_done)
	{	
		s = sphere();
		s.m.color = color(0x1F, 0xCE, 0xCB);
		s.m.diffuse = 0.9;
		s.m.specular = 0.1;
		s.m.shininess = 5;
		float	shear[6] = {.5, 0, 0, 0, 0, 0};
		s.transform = mmultfree(shearing(shear), s.transform);
		s.transform = mmultfree(rotation_y(M_PI/6), s.transform);
		largs.light = point_light(point(5, 10, -10), color(255, 255, 255));
		ray_origin = point(0, 0, -10);
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
				pos = point(world_x, world_y, wall_z);
				r = ray(ray_origin, tnorm(tsub(pos, ray_origin)));
				xs = intersect(&s, r);
				ht = hit(xs);
				if (ht)
				{
					largs.point = position(r, ht->t);
					largs.normalv = normal_at(ht->object, largs.point);
					largs.eyev = tneg(r.direction);
					largs.material = ht->object->m;
					col = lighting(&largs);
					mlx_put_pixel(data->img, x, y, color_to_hex(col));
					free(ht);
				}
				xs[0].object = NULL;
				x++;
			}
			y++;
		}
	}
	if (!render_done)
	{
		free_matrix(s.transform, 4);
		free(xs);
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
