/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 09:36:36 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/01 09:37:19 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	canvas_open_file(char *filename)
{
	int		fd;
	char	*buf;

	buf = ft_calloc(3, sizeof(char));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror("texture: open");
	else if (read(fd, buf, 3) < 0)
		perror("texture: read");
	else if (ft_strncmp(buf, "P3\n", 3))
	{
		ft_putstr_fd("texture: Wrong header!", 2);
		fd = -1;
	}
	free(buf);
	return (fd);
}

static char	canvas_read_next_digit(int fd)
{
	char	buf;
	int		status;

	status = read_next_buffer(&buf, fd, 0);
	if (status > 0 && buf == '#')
	{
		status = skip_line(fd);
		buf = '\n';
	}
	if (status < 0)
	{
		perror("texture: read\n");
		return ('*');
	}
	if (status == 0 || (!ft_isdigit(buf) && buf != ' ' && buf != '\n'))
	{
		ft_putstr_fd("texture: Invalid file\n", 2);
		return ('*');
	}
	return (buf);
}

static int	canvas_read_next_float(int fd, float *n)
{
	char	c;
	char	buf[10];
	int		idx;

	idx = 0;
	while (1)
	{
		c = canvas_read_next_digit(fd);
		if (c == '*')
			return (-1);
		else if (idx == 0 && (c == ' ' || c == '\n'))
			continue ;
		else if (idx > 0 && (c == ' ' || c == '\n'))
		{
			buf[idx] = '\0';
			*n = (float)ft_atoi(buf);
			return (0);
		}
		buf[idx++] = c;
	}
}

static int	canvas_read_image(int fd, t_canvas *canvas)
{
	int		x;
	int		y;
	int		i;
	float	c[3];

	i = 0;
	canvas->img = malloc(canvas->height * sizeof(void *));
	y = -1;
	while (++y < canvas->height)
	{
		canvas->img[y] = malloc(canvas->width * sizeof(t_rgb));
		x = 0;
		while (x < canvas->width)
		{
			while (i < ((x + 1) * 3 + y * canvas->width * 3))
			{
				if (canvas_read_next_float(fd, &c[i++ % 3]))
					return (-1);
				if (c[(i - 1) % 3] < 0 || c[(i - 1) % 3] > canvas->scaling)
					return (ft_putstr_fd("texture: Invalid color\n", 2), -1);
			}
			canvas->img[y][x++] = colorsc(c[0], c[1], c[2], canvas->scaling);
		}
	}
	return (0);
}

t_canvas	*canvas_from_ppm(char *filename)
{
	int			fd;
	t_canvas	*canvas;

	fd = canvas_open_file(filename);
	if (fd < 0)
		return (NULL);
	canvas = ft_calloc(1, sizeof(t_canvas));
	if (!canvas)
		exit (-1);
	if (canvas_read_next_float(fd, &canvas->width))
		return (NULL);
	if (canvas_read_next_float(fd, &canvas->height))
		return (NULL);
	if (canvas_read_next_float(fd, &canvas->scaling))
		return (NULL);
	if (canvas_read_image(fd, canvas))
		return (NULL);
	printf("parsed texture: %s\nwidth: %f, height %f, scaling %f\n",
		filename, canvas->width, canvas->height, canvas->scaling);
	close(fd);
	read_next_buffer(NULL, 0, 1);
	return (canvas);
}
