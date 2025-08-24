/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:08:43 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/24 21:18:59 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <ctype.h>

static int str_contains(char c, char *str);

int	scenefile_check_chars(char *filename)
{
	int		fd;
	char	buf;
	int		comment;

	fd = open_file(filename);
	comment = 0;
	while(read(fd, &buf, 1))
	{
		comment = (!comment && buf == '*') || (comment && buf && buf != '\n');
		if (!comment && !ft_isalnum(buf) && !str_contains(buf, " .,-\n\t"))
		{
			close(fd);
			ft_putstr_fd("ERROR: invalid character found in file: ", 2);
			ft_putstr_fd(filename, 2);
			ft_putstr_fd("!\n", 2);
			rt_early_exit(ERROR_WRONG_CHARS);
		}
	}
	close(fd);
	return(EXIT_SUCCESS);
}

static int str_contains(char c, char *str)
{
	int	found;

	found = 0;
	while(*str && !found)
		if (*str++ == c)
			found++;
	if (found > 0)
		return (1);
	return (0);
}
