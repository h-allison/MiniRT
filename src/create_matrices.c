/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrices.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:20:40 by hallison          #+#    #+#             */
/*   Updated: 2025/09/21 07:16:54 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Create X x Y Matrix

void	free_matrix(float **m, int size)
{
	int	i;

	i = 0;
	if (m)
	{
		while (i < size)
		{
			if (m[i])
				free(m[i]);
			i++;
		}
		free(m);
		m = NULL;
	}
}

// TODO: handle malloc fail

float	**alloc_matrix(int size)
{
	int		i;
	float	**m;

	m = ft_calloc(sizeof(float *), size);
	if (!m)
		exit (1);
	i = 0;
	while (i < size)
	{
		m[i] = ft_calloc(sizeof(float), size);
		if (!m[i])
		{
			free_matrix(m, size);
			exit (1);
		}
		i++;
	}
	return (m);
}

float	**create_id_matrix(void)
{
	float	**id;
	int		i;

	id = alloc_matrix(4);
	i = 0;
	while (i < 4)
	{
		id[i][i] = 1;
		i++;
	}
	return (id);
}
