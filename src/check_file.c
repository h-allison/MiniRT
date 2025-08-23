/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:08:43 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/23 19:02:40 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <ctype.h>

static int str_contains(char c, char *str);

int	scenefile_check_chars(char *filename)
{
	int		fd;
	char	buf;

	fd = open_file(filename);
	while(read(fd, &buf, 1))
	{
		if (!ft_isalnum(buf) && !str_contains(buf, " .:,+-*()[]\n\t"))
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
	int	i;
	int	found;

	i = 0;
	found = 0;
	while(str[i] && !found)
	{
		if (str[i] == c)
			found++;
		i++;
	}
	if (found > 0)
		return (1);
	return (0);
}
