/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:18:54 by hallison          #+#    #+#             */
/*   Updated: 2025/09/29 16:19:38 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

bool	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\0')
		return (true);
	return (false);
}

void	init_checklist(t_world *world)
{
	world->checklist = malloc (sizeof(t_checklist));
	if (!world->checklist)
		exit(1);
	world->checklist->a_parsed = false;
	world->checklist->c_parsed = false;
	world->checklist->l_parsed = false;
	world->checklist->count_light = 0;
	world->checklist->count_sphere = 0;
	world->checklist->count_cyl = 0;
	world->checklist->count_cube = 0;
	world->checklist->count_plane = 0;
	world->checklist->count_cone = 0;
	world->checklist->count_shape = 0;
}

int	count_shape(t_checklist *lst, char *ln)
{
	if (ln[0] == 'p' && ln[1] == 'l' && is_space(ln[2]))
		lst->count_plane++;
	else if (ln[0] == 's' && ln[1] == 'p' && is_space(ln[2]))
		lst->count_sphere++;
	else if (ln[0] == 'c' && ln[1] == 'y' && is_space(ln[2]))
		lst->count_cyl++;
	else if (ln[0] == 'c' && ln[1] == 'b' && is_space(ln[2]))
		lst->count_cube++;
	else if (ln[0] == 'c' && ln[1] == 'n' && is_space(ln[2]))
		lst->count_cone++;
	else if (ln[0] != '*' && !is_space(ln[0]))
	{
		printf("c = %c\n", ln[0]);
		return (rt_error("File incl. unknown identifier", -1));
	}
	return (0);
}

int	count_singular_element(t_checklist *lst, char *ln)
{
	if (ln[0] == 'A' && is_space(ln[1]))
	{
		if (lst->a_parsed == true)
			return (rt_error("A: File incl. more than one ambient", -1));
		lst->a_parsed = true;
	}
	else if (ln[0] == 'C' && is_space(ln[1]))
	{
		if (lst->c_parsed == true)
			return (rt_error("A: File incl. more than one camera", -1));
		lst->c_parsed = true;
	}
	else if (ln[0] == 'L' && is_space(ln[1]))
	{
		if (lst->l_parsed == true && BONUS == false)
			return (rt_error("L: Enable bonus for > 1 light", -1));
		lst->l_parsed = true;
		lst->count_light++;
	}
	else
		return (rt_error("File incl. unknown capital letter identifier", -1));
	return (0);
}

int	fill_checklist_count(t_data *data)
{	
	int	fd;
	char	*ln;

	fd = open_file(data->filename);
	ln = get_next_line(fd);
	while (ln != NULL)
	{
		if (ln[0] >= 'A' && ln[0] <= 'Z')
		{
			if (count_singular_element(data->world->checklist, ln) != 0)
				return (-1);
		}
		else
		{
			if (count_shape(data->world->checklist, ln) != 0)
				return (-1);
		}	
		free (ln);
		ln = get_next_line(fd);
	}
	close(fd);
	return (0);
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

int	start_parsing_routine(t_data *data)
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
			if (parse_into_world(tokens, data) == -1)
			{
				printf("error\n");
				exit (1);
			}
			free_tokens(tokens);
		}
		element = get_next_line(fd);
	}
	distribute_ambient(data->world);
	close(fd);
	return (0);
}

void	alloc_shape_array(t_world *world)
{
	t_checklist	*lst;
	int			count_shape;

	lst = world->checklist;
	count_shape = lst->count_sphere + lst->count_cyl +
		lst->count_cube + lst->count_plane + lst->count_cone;
	world->s = (t_shape **)calloc(sizeof(t_shape *), count_shape + 1);
	if (!world->s)
		exit(1);
	world->checklist->count_shape = count_shape;
}

int	parse_file(char *filename, t_data *data)
{
//	printf("parse_file\n");
//	check_rt_filename(filename);
	data->filename = filename;
//	scenefile_check_chars(data->filename);
	data->world = malloc(sizeof(t_world));
	if (!data->world)
		exit (1);
	init_checklist(data->world);
	if (fill_checklist_count(data) != 0)
	{
		free(data->world);
		exit (1);
	}
	alloc_shape_array(data->world);
	start_parsing_routine(data);
	return (0);
}
