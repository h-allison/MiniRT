/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:18:37 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/23 20:03:41 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


// check identifier:
// check for A, C, L, pl, sp, cy
// if nonsense, exit
// if asterisk (after usable data) okay
// open new function, fill cooresponding struct'
	// on parsing error, print ERROR and exit
// if ACL found twice, abort / exit

int	analyze_line(char *line, t_data *data)
{
	while (*line)
	{
		if ((ft_isalpha(*line))
				// check identifier
	}
	// Is there an empty struct? 
}

int	parse_lines(int fd, t_data  *data)
{
	char *line;
	int	i;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '\n' || line[i] == '*' || !line[i])
		{
			free(line);
			continue ;
		}
		analyze_line(line + i, data);
		free (line);
	}
}

int	parse_file(char *filename, t_data *data)
{
	int fd;

	data->file_name = filename;

	check_rt_filename(filename);
	scenefile_check_chars(filename);
	fd = open_file(filename);
	parse_lines(fd, data);

	data->mlx_ptr = NULL; // TODO
	data->win_ptr = NULL; // TODO
	close(fd);
	return(0);
}
