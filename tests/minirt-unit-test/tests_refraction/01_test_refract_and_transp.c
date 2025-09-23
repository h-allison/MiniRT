/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_test_refract_and_transp.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 23:02:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/23 02:56:40 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "refraction_tests.h"

int test_refract_and_transp(void)
{
	t_material	*m;

	m = material();
	if (m->transparency != 0.0 || m->refractive_index != 1.0)
		return (-1);
	free_matrix(m->pattern->transform, 4);
	free_matrix(m->pattern->invtrans, 4);
	return (0);
}
