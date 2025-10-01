/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 12:09:09 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/01 09:22:07 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	read_next_buffer(char *buf, int fd, int init)
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

int	skip_line(int fd)
{
	char	buf;
	int		status;

	while (1)
	{
		status = read_next_buffer(&buf, fd, 0);
		if (status <= 0 || buf == '\n')
			return (status);
	}
}

static bool	obj_expected(char buf, char *s)
{
	while (s && *s)
		if (buf == *(s++))
			return (true);
	return (false);
}

char	obj_read_next_char(int fd, char *expect)
{
	char	buf;
	char	buf2;
	int		status;

	status = read_next_buffer(&buf, fd, 0);
	if (status > 0 && obj_expected(buf, expect))
	{
		status = read_next_buffer(&buf2, fd, 0);
		if (status > 0 && obj_expected(buf2, " "))
			return (buf);
	}
	if (status > 0 && buf != ' ' && buf != '\n')
	{
		status = skip_line(fd);
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

int	obj_read_next_float(int fd, float *n)
{
	char	c;
	char	buf[20];
	int		idx;
	int		status;

	idx = 0;
	while (1)
	{
		status = read_next_buffer(&c, fd, 0);
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
