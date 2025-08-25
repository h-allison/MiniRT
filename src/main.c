/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:54:44 by hallison          #+#    #+#             */
/*   Updated: 2025/08/25 20:27:29 by hallison         ###   ########.fr       */
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

static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	render(void *param)
{
	static bool	render_done;

	render_done = false;
	struct	s_proj
	{
		t_tuple position;
		t_tuple velocity;
	} ;

	struct	s_env
	{
		t_tuple	gravity;
		t_tuple	wind;
	} ;

	t_data *data;
	struct s_proj	ball;
	struct s_env	env;

	data = (t_data *) param;
	ball.position = create_point(0, 1, 0);
	ball.velocity = tnorm(create_vector(0.8, 1, 0));
	env.gravity = create_vector(0, -0.001, 0);
	env.wind = create_vector(-0.0005, 0, 0);

	while (ball.position.y > 0)
	{
		mlx_put_pixel(data->img, ball.position.x, 600 - ball.position.y, 0xE09558FF);
		ball.position = tadd(ball.position, ball.velocity);
		ball.velocity = tadd(ball.velocity, tadd(env.gravity, env.wind));
	}
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
			mlx_put_pixel(data->img, x++, y, color_to_hex(color));
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
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error(); // TODO
	img_wipe(data, create_color(0x00, 0x0F, 0x99));
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}

