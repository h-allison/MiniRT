/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:54:44 by hallison          #+#    #+#             */
/*   Updated: 2025/10/02 20:27:12 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		rt_early_exit(ERROR_WRONG_ARGS);
	data.reset = true;
	data.cam = NULL;
	data.rs.moving_frames = 0;
	data.rs.moving_active = 0;
	data.rs.chunk_size = STEADY_CHUNK_SIZE;
	data.rs.max_recursion = STEADY_MAX_RECURSION;
	if (parse_file(argv[1], &data) != 0)
	{
		free_world(data.world);
		if (data.cam)
			free_cam(data.cam);
		return (0);
	}
	printf("Time to raytrace!\n");
	mlx_handling(&data);
	return (0);
}
