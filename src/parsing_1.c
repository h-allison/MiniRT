/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:18:54 by hallison          #+#    #+#             */
/*   Updated: 2025/09/18 16:04:18 by hallison         ###   ########.fr       */
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

/*
int	analyze_line(char *line, t_data *data)
{
	(void) data;
	ft_putstr_fd(line, 1);
//	while (*line)
//	{
//		if ((ft_isalpha(*line))
				// check identifier
//	/
	// Is there an empty struct? 
	return (0);
}

int	parse_lines(int fd, t_data *data)
{
	char	*line;
	int		i;

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
	return (0);
}
*/

static void	debug_print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		printf("\t[%i] %s \n", i, tokens[i]);
		i++;
	}
}

// TODO fancier exit
//
int	parse_file(char *filename, t_data *data)
{
	int		fd;
	char	*element;
	char	**tokens;

	check_rt_filename(filename);
	data->filename = filename;
	scenefile_check_chars(data->filename);
	fd = open_file(data->filename);
	element = get_next_line(fd);
	while (element != NULL)
	{
		tokens = get_element_tokens(element);
		free(element);
		if (tokens != NULL)
		{
			debug_print_tokens(tokens);
			if (parse_into_world(tokens, data) == -1)
				exit (1);
			free (tokens);
		}
		element = get_next_line(fd);
	}
	close(fd);
	return (0);
}
