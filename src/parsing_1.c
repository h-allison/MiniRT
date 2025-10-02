/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 11:18:54 by hallison          #+#    #+#             */
/*   Updated: 2025/10/01 16:54:48 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

// TODO: distribute_ambient(data->world);

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
				free_tokens(tokens);
				return (-1);
			}
			free_tokens(tokens);
		}
		element = get_next_line(fd);
	}
	close(fd);
	return (0);
}

void	alloc_shape_array(t_world *world)
{
	t_checklist	*lst;
	int			count_shape;

	lst = world->checklist;
	count_shape = lst->count_sphere + lst->count_cyl
		+ lst->count_cube + lst->count_plane + lst->count_cone;
	world->s = (t_shape **)ft_calloc(sizeof(t_shape *), count_shape + 1);
	if (!world->s)
		exit(1);
	world->checklist->count_shape = count_shape;
}

t_world *init_world(void)
{
	t_world *world;

	world = (t_world *) ft_calloc(sizeof(t_world), 1);
	if (!world)
		exit (1);
	world->s = NULL;
	world->light = NULL;
	world->checklist = NULL;
	return (world);
}

int	parse_file(char *filename, t_data *data)
{
	check_rt_filename(filename);
	data->filename = filename;
	data->world = init_world();
	if (!data->world)
		exit (1);
	init_checklist(data->world);
	if (fill_checklist_count(data) != 0)
		return (-1);
	alloc_shape_array(data->world);
	if (start_parsing_routine(data) != 0)
		return (-1);
	return (0);
}
