/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 17:37:09 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/27 17:52:38 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tri	*triangle(t_tuple p1, t_tuple p2, t_tuple p3)
{
	t_tri	*t;
	
	t = malloc(sizeof(t_tri));
	t->p1 = p1;
	t->p2 = p2;
	t->p3 = p3;
	t->e1 = tsub(p2, p1);
	t->e2 = tsub(p3, p1);
	t->normal = tnorm(cross(t->e2, t->e1));
	return (t);
}
