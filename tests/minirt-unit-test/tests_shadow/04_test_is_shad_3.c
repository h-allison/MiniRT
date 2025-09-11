/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_test_is_shad_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:52:32 by smargine          #+#    #+#             */
/*   Updated: 2025/09/11 22:31:29 by matthias         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shadow_tests.h"
#include "libunit.h"

int test_is_shad_3(void)
{
	t_world w;
	bool	shadowed;

	w = default_world();
	shadowed = is_shadowed(&w, 0, point(-20, 20, -20));
	free_matrix(w.s[0].transform, 4);
	free_matrix(w.s[1].transform, 4);
	free(w.light);
	free(w.s);
	if (!shadowed)
	{
		return (0);
	}
	return (-1);
}
