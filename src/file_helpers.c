/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 17:27:01 by mmillhof          #+#    #+#             */
/*   Updated: 2025/10/02 14:52:35 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_rt_filename(char	*filename)
{
	int	filename_len;

	filename_len = ft_strlen(filename);
	if (filename_len < 4
		|| ft_strncmp (filename + filename_len - 3, ".rt", 3) != 0)
		rt_early_exit(ERROR_FILENAME);
	return (0);
}

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	return (fd);
}

int	close_and_return(int fd, int ret)
{
	close (fd);
	return (ret);
}
