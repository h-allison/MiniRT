/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:32:31 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/05 23:36:51 by mmillhof         ###   ########.fr       */
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
	data->img = mlx_new_image(data->mlx, WIN_WIDTH,	WIN_HEIGHT);
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error(); // TODO
	img_wipe(data, color(0x00, 0x00, 0x00));
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop_hook(data->mlx, ft_hook, data->mlx);
	mlx_loop(data->mlx);	
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		printf("UP\n");
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		printf("DOWN\n");
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		printf("LEFT\n");
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		printf("RIGHT\n");
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
