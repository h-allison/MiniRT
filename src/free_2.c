/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:38:13 by hallison          #+#    #+#             */
/*   Updated: 2025/09/30 15:16:22 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_material(t_material *m)
{
	free_pattern(m->pattern);
	free(m);
	return ;
}

void	free_pattern(t_pattern *p)
{
	if (!p)
		return ;
	free_matrix(p->transform, 4);
	free_matrix(p->invtrans, 4);
	free_pattern(p->uv_pattern);
	if (p->canvas)
		free_canvas(p->canvas);
	free(p);
	return ;
}

void	free_uv_pattern(t_pattern *p)
{
	if (!p)
		return ;
	free_matrix(p->transform, 4);
	free_matrix(p->invtrans, 4);
	if (p->canvas)
		free_canvas(p->canvas);
	free(p);
	return ;
}

void	free_canvas(t_canvas *c)
{
	int	y;

	if (!c)
		return ;
	y = 0;
	while (y < c->height)
		free(c->img[y++]);
	free(c->img);
	free(c);
}
