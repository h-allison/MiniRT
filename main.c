/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:54:44 by hallison          #+#    #+#             */
/*   Updated: 2025/08/22 16:11:06 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer.h"

void	rt_early_exit(int error)
{
	if (error == ERROR_NOFILE)
		ft_putstr_fd("ERROR: Usage: <*.rt>\n", 2);
	else if (error == ERROR_FILENAME)
		ft_putstr_fd("ERROR: Usage: <*.rt>\n", 2);
	else if (error == ERROR_OPEN)
	{	
		perror("ERROR");
		exit(errno);
	}
	exit(1);
}

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		rt_early_exit(ERROR_OPEN);
	return (fd);
}

int	check_rt_filename(char	*filename)
{
	int	filename_len;

	filename_len = ft_strlen(filename);
	if (filename_len < 4 || ft_strncmp (filename + filename_len - 3, ".rt", 3) != 0)
		rt_early_exit(ERROR_FILENAME);
	return (0);
}

int	parse_file(char *filename, t_data *data)
{
	int fd;

	check_rt_filename(filename);
	fd = open_file(filename);
	data->file_name = filename;
	data->mlx_ptr = NULL; // TODO
	data->win_ptr = NULL; // TODO
	close(fd);
	return(0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		rt_early_exit(ERROR_NOFILE);
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
