/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_intersections_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:56:16 by hallison          #+#    #+#             */
/*   Updated: 2025/09/15 17:48:49 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	*intersect_world(t_world *w, t_ray *r)
{
	int				i;
	t_intersection	*xs;

	i = 0;
	while (w->s[i].transform)
	{
		xs = intersect(&w->s[i], *r);
		i++;
	}
	return (xs);
}

void	lst_findobject(t_list *containers, t_shape *object)
{
	t_list	*new_next;
	t_list  *new_node;

	while (containers->next)
	{
		if (containers->next->content == object)
		{
			if (containers->next)
				new_next = containers->next->next;
			else
				new_next = NULL;
			free(containers->next);
			containers->next = new_next;
			return;
		}
		containers = containers->next;
	}
	new_node = ft_lstnew(object);
	containers->next = new_node;
	return;
}

void	prepare_n(t_comps *comps, t_intersection *ht, t_intersection *xs)
{
	t_list			*containers;
	int				i;
	t_shape			*object;
	
	containers = ft_lstnew(NULL);
	i = 0;
	while (xs[i].object)
	{
		if (xs[i].t == ht->t && xs[i].object == ht->object)
		{
			if (!containers->next)
				comps->n1 = 1.0;
			else
			{
				object = (t_shape *)ft_lstlast(containers)->content;
				comps->n1 = object->m.refractive_index;
			}
		}
		lst_findobject(containers, ht->object); // check if containers includes xs[i].object
		if (xs[i].t == ht->t && xs[i].object == ht->object)
		{
			if (!containers->next)
				comps->n2 = 1.0;
			else
			{
				object = (t_shape *)ft_lstlast(containers)->content;
				comps->n1 = object->m.refractive_index;
			}
		}
		i++;
	}
	ft_lstclear(&containers, &free);
}

t_comps	prepare_computations(t_intersection *ht, t_ray *r, t_intersection *xs)
{
	t_comps	comps;

	comps.t = ht->t;
	comps.object = ht->object;
	comps.point = position(*r, comps.t);
	comps.eyev = tneg(r->direction);
	comps.normalv = normal_at(comps.object, comps.point);
	comps.reflectv = reflect(r->direction, comps.normalv);
	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = true;
		comps.normalv = tneg(comps.normalv);
	}
	else
		comps.inside = false;
	comps.over_point = tadd(comps.point, (tmult(comps.normalv, OFFSET)));
	prepare_n(&comps, ht, xs);
	return (comps);
}
