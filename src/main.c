/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:54:44 by hallison          #+#    #+#             */
/*   Updated: 2025/09/30 21:33:57 by mmillhof         ###   ########.fr       */
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
	if (parse_file(argv[1], &data) != 0)
	{
		free_world(data.world);
		if (data.cam)
		{
			free_matrix(data.cam->transform, 4);
			free(data.cam);
		}
		return (0);
	}
	printf("Time to raytrace!\n");
	mlx_handling(&data);
	return (0);
}
