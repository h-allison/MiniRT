/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 12:09:09 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/01 09:27:31 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	obj_add_face(int fd, t_parser *parser)
{
	(void)fd;
	(void)parser;
	printf("\nADD FACE");
	return (1);
}

static int	obj_add_vertex(int fd, t_parser *parser)
{
	int		i;
	int		status;
	float	f[3];

	i = 0;
	status = 0;
	while (i < 3)
	{
		status = obj_read_next_float(fd, &f[i++]);
		if (status < 0 || (status == 0 && i < 3))
			return (-1);
	}
	if (!parser->vertices)
	{
		parser->vertices = malloc(101 * sizeof(t_tuple));
		parser->vertices[0].x = 100;
		parser->vertices[0].y = 0;
	}
	parser->vertices[1 + (int)parser->vertices->y] = point(f[0], f[1], f[2]);
	parser->vertices->y = parser->vertices->y + 1;
	return (status);
}

static int	obj_read_file(int fd, t_parser *parser)
{
	int		status;
	char	buf;

	while (1)
	{
		buf = obj_read_next_char(fd, "vf");
		if (buf == '#' || buf == ' ' || buf == '\n')
		{
			parser->ignored += (buf == '#');
			continue ;
		}
		if (buf == '%')
			break ;
		if (buf == '*')
			return (-1);
		if (buf == 'v')
			status = obj_add_vertex(fd, parser);
		if (buf == 'f')
			status = obj_add_face(fd, parser);
		if (status < 0 || (status == 0 && parser->vertices[0].y == 0)) 
			return (-1);
	}
	return (0);
}

static int	obj_open_file(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		perror("texture: open");
	return (fd);
}

t_parser	*parse_obj_file(char *filename)
{
	int			fd;
	t_parser	*parser;

	fd = obj_open_file(filename);
	if (fd < 0)
		return (NULL);
	parser = ft_calloc(1, sizeof(t_parser));
	if (!parser)
		exit (-1);
	if (obj_read_file(fd, parser))
		return (NULL);
	close(fd);
	read_next_buffer(NULL, 0, 1);
	return (parser);
}
