/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:38:13 by hallison          #+#    #+#             */
/*   Updated: 2025/09/30 15:15:31 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_cam(t_camera *cam)
{
	free_matrix(cam->transform, 4);
	free(cam);
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

void	free_largs(t_largs *l)
{
	free_shape(l->shape);
	free_material(l->material);
	free(l->light);
	free(l);
	return ;
}
