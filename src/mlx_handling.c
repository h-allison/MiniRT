/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:32:31 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/18 18:21:03 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int	mlx_handling(t_data *data)
{
	data->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, data->filename, true);
	if (!data->mlx)
		ft_error(); // TODO
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error(); // TODO
	img_wipe(data, color(0x00, 0x00, 0x00));
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}

void	ft_hook(void *param)
{
	static bool	init;
	t_data		*data;

	if (!init)
	{
		data = (t_data *)param;
		init = true;
	}
	if (init)
	{
		if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
			mlx_close_window(data->mlx);
		if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		{
			data->cam->transform = mmultfree(translation(0, 0, 0.1), data->cam->transform);
			data->reset = true;
			printf("Move FORWARD\n");
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		{
			data->cam->transform = mmultfree(translation(0, 0, -0.1), data->cam->transform);
			data->reset = true;
			printf("Move BACKWARD\n");
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		{
			data->cam->transform = mmultfree(translation(-0.1, 0, 0), data->cam->transform);
			data->reset = true;
			printf("Move LEFT\n");
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		{
			data->cam->transform = mmultfree(translation(0.1, 0, 0), data->cam->transform);
			data->reset = true;
			printf("Move RIGHT\n");
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_R))
		{
			data->cam->transform = mmultfree(translation(0, -0.1, 0), data->cam->transform);
			data->reset = true;
			printf("Move UP\n");
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_F))
		{
			data->cam->transform = mmultfree(translation(0, 0.1, 0), data->cam->transform);
			data->reset = true;
			printf("Move DOWN\n");
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		{
			data->cam->transform = mmultfree(rotation_x(-1 * DEG2RAD), data->cam->transform);
			data->reset = true;
			printf("Rotate UP\n");
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		{
			data->cam->transform = mmultfree(rotation_x(1 * DEG2RAD), data->cam->transform);
			data->reset = true;
			printf("Rotate DOWN\n");
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		{
			data->cam->transform = mmultfree(rotation_y(1 * DEG2RAD), data->cam->transform);
			data->reset = true;
			printf("Rotate LEFT\n");
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		{
			data->cam->transform = mmultfree(rotation_y(-1 * DEG2RAD), data->cam->transform);
			data->reset = true;
			printf("Rotate RIGHT\n");
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
		{
			data->cam->transform = mmultfree(rotation_z(-1 * DEG2RAD), data->cam->transform);
			data->reset = true;
			printf("Tilt LEFT\n");
		}
		if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		{
			data->cam->transform = mmultfree(rotation_z(1 * DEG2RAD), data->cam->transform);
			data->reset = true;
			printf("Tilt RIGHT\n");
		}
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
