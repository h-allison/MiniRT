/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:18:54 by hallison          #+#    #+#             */
/*   Updated: 2025/09/22 20:37:46 by hallison         ###   ########.fr       */
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
*/

// TODO fancier exit

bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\0')
		return (true)
	return (false);
}

int	fill_checklist_count(t_data *data)
{	
	int	fd;
	char	*ln;

	fd = open_file(data->filename);
	ln = get_next_line(fd);
	while (line != NULL)
	{
		if (ln[0] == 'p' && ln[1] == 'l' && is_space(ln[2]))
			count_plane++;
		else if (ln[0] == 'sp' && ln[1] == 'l' && is_space(ln[2]))
			
		free (line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	init_checklist(t_checklist *checklist)
{
	checklist->a_parsed = false;
	checklist->c_parsed = false;
	checklist->l_parsed = false;
	count_light = 0;
	count_sphere = 0;
	count_cyl = 0;
	count_cube = 0;
	count_plane = 0;
}

int	parse_file_2(t_data *data)
{
	int		fd;
	char	*element;
	char	**tokens;

	fd = open_file(data->filename);
	if (fd < 0)
		exit (1);
	element = get_next_line(fd);
	while (element != NULL)
	{
		tokens = get_element_tokens(element);
		free(element);
		if (tokens != NULL)
		{
		//	debug_print_tokens(tokens);
			if (parse_into_world(tokens, data) == -1)
			{
				printf("error\n");
				exit (1);
			}
			free (tokens); // TODO
		}
		element = get_next_line(fd);
	}
	close(fd);
}

int	parse_file(char *filename, t_data *data)
{
	check_rt_filename(filename);
	data->filename = filename;
	scenefile_check_chars(data->filename);
	data->world = malloc(sizeof(t_world));
	if (!data->world)
		exit (1);
	init_checklist(&data->world->checklist);
	fill_checklist_count(data);
	parse_file_2(data);
	return (0);
}
