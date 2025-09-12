/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_test_shape_ass_material.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:35:47 by hallison          #+#    #+#             */
/*   Updated: 2025/09/12 12:14:58 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes_tests.h"

static int	free_matrices_and_return(t_shape *p, int ret)
{
	if (p->transform)
		free_matrix(p->transform, 4);
	if (p->invtrans)
		free_matrix(p->invtrans, 4);
	if (p->m.pattern.transform)
		free_matrix(p->m.pattern.transform, 4);
	if (p->m.pattern.invtrans)
		free_matrix(p->m.pattern.invtrans, 4);
	return (ret);
}

static void	free_material(t_shape *s)
{
	if (s->m.pattern.transform)
		free_matrix(s->m.pattern.transform, 4);
	if (s->m.pattern.invtrans)
		free_matrix(s->m.pattern.invtrans, 4);
}

int test_shape_ass_material(void)
{
	t_shape	s;
	t_material	m;

	s = create_test_shape();
	m = material();
	m.ambient = 1;
	free_material(&s);
	s.m = m;
    if (s.m.ambient == m.ambient)
			return(free_matrices_and_return(&s, 0));
	return(free_matrices_and_return(&s, -1));
}
