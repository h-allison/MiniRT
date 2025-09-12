/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_test_is_shad_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:52:32 by smargine          #+#    #+#             */
/*   Updated: 2025/09/12 13:23:17 by hallison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow_tests.h"
#include "libunit.h"

int test_is_shad_4(void)
{
	t_world w;
	bool	shadowed;

	w = default_world();
	shadowed = is_shadowed(&w, 0, point(-2, 2, -2));
	free_matrices_and_ret(&w.s[0], 0);
	free_matrices_and_ret(&w.s[1], 0);
	free(w.light);
	free(w.s);
	if (!shadowed)
	{
		return (0);
	}
	return (-1);
}
