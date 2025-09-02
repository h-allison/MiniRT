/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:54:44 by hallison          #+#    #+#             */
/*   Updated: 2025/09/02 14:22:34 by mmillhof         ###   ########.fr       */
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
	float			**st;
	float			**sc;
	float			**m;
	t_ray			r;
	int				x;
	int				y;
	t_intersection	*t;
	t_intersection	*xs;

	data = (t_data *)param;
	render_done = false;
	st = translation(400, 300, 300);
	sc = scaling(200, 200, 200);
	m = matrixmult(st, sc);
	free(st);
	free(sc);
	s = sphere(point(0, 0, 0), color(1, 1, 1));
	set_transform(&s, m);
	free(m);
	y = 0;
	while (!render_done && y < 600)
	{
		x = 0;
		while (x < 800)
		{
			
			r = ray(point(0, 0, 0), vector((x - 400), (y - 300), 1));
			xs = intersect(s, r);
			t = hit(xs);
			if (t)
			{
				printf("I");
				mlx_put_pixel(data->img, x, y, color_to_hex(t->object->color));
				free(t);
			}
			xs[0].object = NULL;
			x++;
		}
		y++;
	}
	free(xs);
	if (render_done == false)
	{
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
	data->mlx = mlx_init(800, 600, data->filename, true);
	if (!data->mlx)
		ft_error(); // TODO
	data->img = mlx_new_image(data->mlx, 800, 600);
	img_wipe(data, color(0x00, 0x00, 0x00));
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error(); // TODO
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
