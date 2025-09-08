/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ppm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:40:41 by hallison          #+#    #+#             */
/*   Updated: 2025/09/09 00:46:46 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	write_ppm_header(int fd, t_data *data)
{
	char	*width;
	char	*height;

	width = ft_itoa(data->mlx->width);
	height = ft_itoa(data->mlx->height);
	write(fd, "P3\n", 3);
	ft_putstr_fd(width, fd);
	write(fd, " ", 1);
	ft_putstr_fd(height, fd);
	write(fd, "\n", 1);
	write(fd, "255\n", 4);
	free(width);
	free(height);
	return (0);
}

void	write_pixel_fd(int fd, uint8_t *pixel)
{
	char	*str;
	int		i;

	i = 0;
	while (i < 3)
	{
		str = ft_itoa(*(pixel + i++));
		ft_putstr_fd(str, fd);
		free(str);
		write(fd, " ", 1);
	}
}

int	write_pixel_data(int fd, t_data *data)
{
	int		size;
	uint8_t	*pixel;
	int		i;

	i = 0;
	pixel = data->img->pixels;
	size = data->mlx->height * data->mlx->width * 4;
	while (i < size)
	{
		write_pixel_fd(fd, pixel + i);
		if (i % 50 == 0)
			write(fd, "\n", 1);
		i = i + 4;
	}
	return (0);
}

// TODO name increases if already exists

int	canvas_export_ppm(t_data *data)
{
	int		fd;
	char	*filename;

	filename = "./export.ppm";
	fd = open(filename, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		exit (1);
	write_ppm_header(fd, data);
	write_pixel_data(fd, data);
	close(fd);
	return (0);
}
