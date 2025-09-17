/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_test_cyls_local_normal.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:12:11 by hallison          #+#    #+#             */
/*   Updated: 2025/09/17 21:29:23 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub_cyl_tests.h"

int test_cyls_local_normal(void)
{
	t_shape			cyl;
	t_tuple			n;

	cyl = cylinder();

	// Example 1
	n = local_normal_at_cyl(&cyl, point(1, 0, 0));
	if (n.x != 1 ||  n.y != 0 || n.z != 0)
		return(-1);

	// Example 2
	n = local_normal_at_cyl(&cyl, point(0, 5, -1));
	if (n.x != 0 ||  n.y != 0 || n.z != -1)
		return(-1);
	
	// Example 3
	n = local_normal_at_cyl(&cyl, point(-1, 1, 0));
	if (n.x != -1 ||  n.y != 0 || n.z != 0)
		return(-1);
	return (0);
}
