/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:50:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/26 17:13:58 by mmillhof         ###   ########.fr       */
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
	{
		perror("texture: open");
	}
	else if (read(fd, buf, 3) < 0)
	{
		perror("texture: read");
	}
	else if (ft_strncmp(buf, "P3\n", 3))
	{
		ft_putstr_fd("texture: Wrong header!", 2);
		fd = -1;
	}
	free(buf);
	return (fd);
}

static int	canvas_skip_comment(int fd)
{
	char	buf;
	int		status;

	while (1)
	{
		status = read(fd, &buf, 1);
		if (status <= 0 || buf == '\n')
			return (status);
	}
}

static char	canvas_read_next_char(int fd)
{
	char	buf;
	int		status;

	status = read(fd, &buf, 1);
	if (status > 0 && buf == '#')
	{
		status = canvas_skip_comment(fd);
		buf = '\n';
	}
	if (status < 0)
	{
		perror("texture: read");
		return ('*');
	}
	if (status == 0 || (!ft_isdigit(buf) && buf != ' ' && buf != '\n'))
	{
		ft_putstr_fd("texture: Invalid file", 2);
		return ('*');
	}
	return (buf);
}

static int	canvas_read_next_digit(int fd, float *n)
{
	char	c;
	char	buf[10];
	int		idx;

	idx = 0;
	while (1)
	{
		c = canvas_read_next_char(fd);
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
				if (canvas_read_next_digit(fd, &c[i++ % 3]))
					return (-1);
				if (c[(i - 1) % 3] < 0 || c[(i - 1) % 3] > canvas->scaling)
					return (ft_putstr_fd("texture: Invalid color", 2), -1);
			}
			canvas->img[y][x++] = color_scale(c[0], c[1], c[2], canvas->scaling);
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
	if (canvas_read_next_digit(fd, &canvas->width))
		return (NULL);
	if (canvas_read_next_digit(fd, &canvas->height))
		return (NULL);
	if (canvas_read_next_digit(fd, &canvas->scaling))
		return (NULL);
	if (canvas_read_image(fd, canvas))
		return (NULL);
	close (fd);
	return (canvas);
}

t_rgb	pixel_at(t_canvas *canvas, int x, int y)
{
	return (canvas->img[y][x]);
}
