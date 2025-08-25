/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_ppm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:40:41 by hallison          #+#    #+#             */
/*   Updated: 2025/08/25 20:19:25 by hallison         ###   ########.fr       */
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
	return (0);
}

void	write_pixel_fd(int fd, uint8_t *pixel)
{
	ft_putstr_fd(ft_itoa(*pixel), fd);
	write(fd, " ", 1);
	ft_putstr_fd(ft_itoa(*(pixel + 1)), fd);
	write(fd, " ", 1);
	ft_putstr_fd(ft_itoa(*(pixel + 2)), fd);
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
		else
			write(fd, " ", 1);
		i = i + 4;
	}
	return (0);
}

int	canvas_export_ppm(t_data *data)
{
	int		fd;
	char	*filename;

	filename = "./export.ppm"; // TODO name increases if already exists
	fd = open(filename, O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		exit (1);
	write_ppm_header(fd, data);
	write_pixel_data(fd, data);
	close(fd);
	return (0);
}
