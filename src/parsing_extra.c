/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:27:35 by hallison          #+#    #+#             */
/*   Updated: 2025/10/02 20:39:27 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	gnl_to_end(char *line, int fd)
{
	free(line);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
}

int	free_all_this_nonsense(char **tokens, int fd, char *element)
{
	free_tokens(tokens);
	element = get_next_line(fd);
	while (element != NULL)
	{
		free(element);
		element = get_next_line(fd);
	}
	return (close_and_return(fd, -1));
}
