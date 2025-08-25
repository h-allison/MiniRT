/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:54:44 by hallison          #+#    #+#             */
/*   Updated: 2025/08/25 15:53:45 by hallison         ###   ########.fr       */
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
	typedef struct	s_proj
	{
		t_tuple position;
		t_tuple velocity;
	} t_proj;

	typedef struct	s_env
	{
		t_tuple	gravity;
		t_tuple	wind;
	} t_env;

	t_data *data;
	t_proj	ball;
	t_env	env;

	data = (t_data *) param;
	ball.position = point(0, 1, 0);
	ball.velocity = tnorm(vector(0.5, 1, 0));
	env.gravity = vector(0, -0.001, 0);
	env.wind = vector(-0.0003, 0, 0);

	while (ball.position.y > 0)
	{
		mlx_put_pixel(data->img, ball.position.x, 600 - ball.position.y, 0xFF0000FF);
		ball.position = tadd(ball.position, ball.velocity);
		ball.velocity = tadd(ball.velocity, tadd(env.gravity, env.wind));
	}
}

int	mlx_handling(t_data *data)
{
	data->mlx = mlx_init(800, 600, data->filename, true);
	if (!data->mlx)
		ft_error(); // TODO
	data->img = mlx_new_image(data->mlx, 800, 600);
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error(); // TODO
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}

