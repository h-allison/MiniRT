/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_intersections_3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:56:16 by hallison          #+#    #+#             */
/*   Updated: 2025/09/30 15:48:05 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	lst_findobject(t_list *containers, t_shape *object)
{
	t_list	*new_next;
	t_list	*new_node;

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
			return ;
		}
		containers = containers->next;
	}
	new_node = ft_lstnew(object);
	containers->next = new_node;
	return ;
}

static void	clear_list(t_list **lst)
{
	t_list	*node;
	t_list	*temp;

	node = *lst;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
	*lst = NULL;
}

static void	set_n(t_list *containers, float *n)
{
	t_shape			*object;
	
	if (containers->next == NULL)
		*n = 1.0;
	else
	{
		object = (t_shape *)ft_lstlast(containers)->content;
		*n = object->m->refractive_index;
	}
}

void	prepare_n(t_comps *comps, t_intersection *ht, t_intersection *xs)
{
	t_list			*containers;
	int				i;

	containers = ft_lstnew(NULL);
	i = 0;
	while (xs && xs[i].object)
	{
		if (xs[i].t == ht->t && xs[i].object == ht->object)
			set_n(containers, &comps->n1);
		lst_findobject(containers, xs[i].object);
		if (xs[i].t == ht->t && xs[i].object == ht->object)
			set_n(containers, &comps->n2);
		i++;
	}
	clear_list(&containers);
}
