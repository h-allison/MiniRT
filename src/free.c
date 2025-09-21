/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:38:13 by hallison          #+#    #+#             */
/*   Updated: 2025/09/21 04:50:14 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


/* Frees all matrices in a given shape and returns ret*/

int	free_matrices_and_ret(t_shape *p, int ret)
{
	if (p->transform)
		free_matrix(p->transform, 4);
	if (p->invtrans)
		free_matrix(p->invtrans, 4);
	if (p->m.pattern.transform)
		free_matrix(p->m.pattern.transform, 4);
	if (p->m.pattern.invtrans)
		free_matrix(p->m.pattern.invtrans, 4);
	return(ret);
}

void	free_shape(t_shape *s)
{
	int	i;

	if (s->group)
	{
		i = 0;
		while (s->group[i])
			free_shape(s->group[i++]);
		free(s->group);
	}
	free_matrix(s->transform, 4);
	free_matrix(s->invtrans, 4);
	free_matrix(s->m.pattern.transform, 4);
	free_matrix(s->m.pattern.invtrans, 4);
	return ;
}

void	free_world(t_world *w)
{
	int	i;

	i = 0;
	while (w->s[i].transform)
		free_shape(&w->s[i++]);
	free(w->s);
	free(w->light);
}
