/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:54:44 by hallison          #+#    #+#             */
/*   Updated: 2025/08/24 23:42:57 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		rt_early_exit(ERROR_WRONG_ARGS);
	parse_file(argv[1], &data);
	printf("Time to raytrace!\n");
//		data.points = projectpoints(&data.map);
//		scale_and_center(&data.map, data.points);
//		setup_graphics(&data);
//		mlx_loop_hook(data.mlx_ptr, &render, &data);
//		mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
//		mlx_hook(data.win_ptr, 17, 0, &close_win, &data);
//		mlx_loop(data.mlx_ptr);
//		free_all(&data.map, &data);
	exit(0);
}
