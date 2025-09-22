/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_intersections_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:56:16 by hallison          #+#    #+#             */
/*   Updated: 2025/09/22 16:02:59 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	swap_xs(t_intersection *a, t_intersection *b)
{
	float		tmp_t;
	t_shape		*tmp_o;

	tmp_t = a->t;
	tmp_o = a->object;
	a->t = b->t;
	a->object = b->object;
	b->t = tmp_t;
	b->object = tmp_o;
	return ;
}	

void	sort_intersections(t_intersection *xs)
{
	int		i;

	i = 0;
	while(xs[i + 1].object)
	{
		if (xs[i].t > xs[i + 1].t)
		{
			swap_xs(&xs[i], &xs[i + 1]);
			i = 0;
		}
		else
			i++;
	}
	return ;
}

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

void    clear_list(t_list **lst) 
{
    t_list  *node;
    t_list  *temp;

    node = *lst;
    while (node)
    {   
        temp = node->next;
        free(node);
        node = temp;
    }
    *lst = NULL;
}


void	prepare_n(t_comps *comps, t_intersection *ht, t_intersection *xs)
{
	t_list			*containers;
	int				i;
	t_shape			*object;
	
	containers = ft_lstnew(NULL);
	i = 0;
	while (xs && xs[i].object)
	{
		if (xs[i].t == ht->t && xs[i].object == ht->object)
		{
			if (containers->next == NULL)
				comps->n1 = 1.0;
			else
			{
				object = (t_shape *)ft_lstlast(containers)->content;
				comps->n1 = object->m.refractive_index;
			}
		}
		lst_findobject(containers, xs[i].object);
		if (xs[i].t == ht->t && xs[i].object == ht->object)
		{
			if (containers->next == NULL)
				comps->n2 = 1.0;
			else
			{
				object = (t_shape *)ft_lstlast(containers)->content;
				comps->n2 = object->m.refractive_index;
			}
		}
		i++;
	}
	clear_list(&containers);
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
	comps.under_point = tsub(comps.point, (tmult(comps.normalv, OFFSET)));
	prepare_n(&comps, ht, xs);
	return (comps);
}
