/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 23:32:31 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/30 21:01:41 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	ft_error(void)
{
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	exit(EXIT_FAILURE);
}

int	mlx_handling(t_data *data)
{
	data->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, data->filename, true);
	if (!data->mlx)
		ft_error();
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img || (mlx_image_to_window(data->mlx, data->img, 0, 0) < 0))
		ft_error();
	img_wipe(data, color(0x00, 0x00, 0x00));
	mlx_loop_hook(data->mlx, render_with_parsing, data);
	mlx_loop_hook(data->mlx, mlx_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}

static void	mlx_check_keys_alpha(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		keypress_s(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		keypress_w(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		keypress_a(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		keypress_d(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_R))
		keypress_r(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_F))
		keypress_f(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
		keypress_q(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		keypress_e(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_P))
		keypress_p(data);
}

static void	mlx_check_keys_esc_cursor(t_data *data)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		keypress_escape(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		keypress_up(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		keypress_down(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		keypress_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		keypress_right(data);
}

void	mlx_hook(void *param)
{
	static bool			init;
	static t_data		*data;

	if (!init)
	{
		data = (t_data *)param;
		init = true;
	}
	if (init)
	{
		mlx_check_keys_esc_cursor(data);
		mlx_check_keys_alpha(data);
	}
}
