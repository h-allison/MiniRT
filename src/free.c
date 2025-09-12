/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 12:38:13 by hallison          #+#    #+#             */
/*   Updated: 2025/09/12 12:43:56 by hallison         ###   ########.fr       */
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
