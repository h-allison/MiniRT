/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 12:32:13 by hallison          #+#    #+#             */
/*   Updated: 2025/09/24 13:03:56 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	btwn_negative_and_positive_1(t_tuple t)
{
	if (t.x < -1 || t.x > 1)
		return (false);
	if (t.y < -1 || t.y > 1)
		return (false);
	if (t.z < -1 || t.z > 1)
		return (false);
	return (true);
}

void	debug_print_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		printf("\t[%i] %s \n", i, tokens[i]);
		i++;
	}
}
