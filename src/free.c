/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:38:13 by hallison          #+#    #+#             */
/*   Updated: 2025/09/29 23:10:13 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_largs(t_largs *l)
{
	free_shape(l->shape);
	free_material(l->material);
	free(l->light);
	free(l);
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

void	free_material(t_material *m)
{
	free_pattern(m->pattern);
	free(m);
	return ;
}

void	free_shape(t_shape *s)
{
	int	i;

	if (!s)
		return ;
	if (s->group)
	{
		i = 0;
		while (s->group[i])
			free_shape(s->group[i++]);
		free(s->group);
	}
	free_matrix(s->transform, 4);
	free_matrix(s->invtrans, 4);
	free_material(s->m);
	free(s);
	return ;
}

void	free_world(t_world *w)
{
	int	i;

	i = 0;
	while (w->s[i])
		free_shape(w->s[i++]);
	free(w->s);
	i = 0;
	while (w->light[i])
		free(w->light[i++]);
	free(w->light);
	free(w->checklist);
	free(w);
}

void	free_cam(t_camera *cam)
{
	free_matrix(cam->transform, 4);
	free(cam);
}
