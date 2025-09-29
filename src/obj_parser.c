/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 12:09:09 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/28 20:24:25 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	obj_open_file(char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("texture: open");
	}
	return (fd);
}

static int	obj_read_next_buffer(char *buf, int fd, int init)
{
	static char	stash[100001];
	static int	i;
	int			status;

	if (init)
	{
		stash[0] = '\0';
		i = 0;
		return (0);
	}
	if (!stash[i])
	{
		status = read(fd, stash, 100000);
		if (status < 0)
			return (-1);
		if (status == 0)
			return (0);
		stash[status + 1] = '\0';
		i = 0;
	}
	*buf = stash[i++];
	return (1);
}

static int	obj_skip_gibberish(int fd)
{
	char	buf;
	int		status;

	while (1)
	{
		status = obj_read_next_buffer(&buf, fd, 0);
		if (status <= 0 || buf == '\n')
			return (status);
	}
}

static bool	obj_expected(char buf, char* s)
{
	while (s && *s)
		if (buf == *(s++))
			return (true);
	return (false);
}

static char	obj_read_next_char(int fd, char *s)
{
	char	buf;
	char	buf2;
	int		status;

	status = obj_read_next_buffer(&buf, fd, 0);
	if (status > 0 && obj_expected(buf, s))
	{
		status = obj_read_next_buffer(&buf2, fd, 0);
		if (status > 0 && obj_expected(buf2, " "))
			return (buf);
	}
	if (status > 0 && buf != ' ' && buf != '\n')
	{
		status = obj_skip_gibberish(fd);
		buf = '#';
	}
	else if (status == 0)
		buf = '%';
	else if (status < 0)
	{
		perror("obj_parser: read");
		buf = '*';
	}
	return (buf);
}

static int	obj_read_next_float(int fd, float *n)
{
	char	c;
	char	buf[20];
	int		idx;
	int		status;

	idx = 0;
	while (1)
	{
		status = obj_read_next_buffer(&c, fd, 0);
		if (status <= 0 || !obj_expected(c, "-.0123456789 \n"))
		{
			printf("obj: Invalid file");
			return (-1);
		}
		else if (idx == 0 && (c == ' '))
			continue ;
		else if (idx > 0 && (c == ' ' || c == '\n'))
		{
			buf[idx] = '\0';
			*n = atof(buf);
			return (1);
		}
		buf[idx++] = c;
	}
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

static int	obj_add_face(int fd, t_parser *parser)
{
	(void)fd;
	(void)parser;

	printf("\nADD FACE");
	return (1);
}

static int	obj_read_file(int fd, t_parser *parser)
{
	int		i;
	int		status;
	char	buf;

	i = 0;
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
		if (status < 0 || (status == 0 && parser->vertices[0].y == 0 )) 
			return (-1);
	}
	(void)i;
	return (0);
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
	obj_read_next_buffer(NULL, 0, 1);
	return (parser);
}
