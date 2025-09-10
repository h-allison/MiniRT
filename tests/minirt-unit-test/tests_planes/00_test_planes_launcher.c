/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_test_planes_launcher.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:07:39 by hallison          #+#    #+#             */
/*   Updated: 2025/09/10 13:39:00 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "planes_tests.h"
#include "libunit.h"

int	planes_tests_launcher(void)
{
	t_unit_test	testlist[2];
	int			ret;

	testlist[0].test = NULL;
	load_test(testlist, "PLANES: test plane", &test_plane);
	ret = launch_tests(testlist);
	return (ret);
}
