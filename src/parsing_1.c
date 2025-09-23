/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:18:54 by hallison          #+#    #+#             */
/*   Updated: 2025/09/23 15:56:21 by hallison         ###   ########.fr       */
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
		return (true);
	return (false);
}

int	fill_checklist_count(t_data *data)
{	
	int	fd;
	char	*ln;

	fd = open_file(data->filename);
	ln = get_next_line(fd);
	while (ln != NULL)
	{
		if (ln[0] == 'p' && ln[1] == 'l' && is_space(ln[2]))
			data->world->checklist.count_plane++;
		else if (ln[0] == 's' && ln[1] == 'p' && is_space(ln[2]))
			data->world->checklist.count_sphere++;
		else if (ln[0] == 'c' && ln[1] == 'y' && is_space(ln[2]))
			data->world->checklist.count_cyl++;
		else if (ln[0] == 'c' && ln[1] == 'b' && is_space(ln[2]))
			data->world->checklist.count_cube++;
		else if (ln[0] == 'c' && ln[1] == 'n' && is_space(ln[2]))
			data->world->checklist.count_cube++;
		else if (ln[0] == 'L' && is_space(ln[1]))
		{
			data->world->checklist.count_light++;
			if (!BONUS && data->world->checklist.count_light > 1)
				return (rt_error("Bonus must be enabled to support multiple lights", -1));
		}
		free (ln);
		ln = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	init_checklist(t_checklist *checklist)
{
	checklist->a_parsed = false;
	checklist->c_parsed = false;
	checklist->l_parsed = false;
	checklist->count_light = 0;
	checklist->count_sphere = 0;
	checklist->count_cyl = 0;
	checklist->count_cube = 0;
	checklist->count_plane = 0;
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free (tokens);
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
	return (0);
}

void	alloc_shape_array(t_world *world)
{
	t_checklist	lst;
	int			count_shape;

	lst = world->checklist;
	count_shape = lst.count_sphere + lst.count_cyl +
		lst.count_cube + lst.count_plane + lst.count_cone;
	world->s = malloc((count_shape + 1) * sizeof(t_shape));
	if (!world->s)
		exit(1);
	world->checklist.count_shape = count_shape;
}

int	parse_file(char *filename, t_data *data)
{
	check_rt_filename(filename);
	data->filename = filename;
	scenefile_check_chars(data->filename);
	data->world = malloc(sizeof(t_world));
	if (!data->world)
		exit (1);
/*	init_checklist(&data->world->checklist);
	if (fill_checklist_count(data) != 0)
	{
		free(data->world);
		exit (1);
	}
	alloc_shape_array(data->world);
	parse_file_2(data);
*/
return (0);
}
