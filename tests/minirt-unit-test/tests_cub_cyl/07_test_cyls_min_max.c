/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_test_cyls_min_max.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:53:28 by hallison          #+#    #+#             */
/*   Updated: 2025/09/23 03:31:45 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_cyl_tests.h"



int test_cyls_min_max(void)
{
	t_shape			*cyl;

	cyl = cylinder();
	if (!fisequal(cyl->minimum, -FLT_MAX) || !fisequal(cyl->maximum, FLT_MAX))
		return(-1);
	free_shape(cyl);
	return (0);
}
