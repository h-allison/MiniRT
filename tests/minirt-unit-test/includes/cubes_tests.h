/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubes_tests.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 17:44:02 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/16 23:18:03 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_TESTS_H
# define CUBE_TESTS_H

# include "libunit.h"
# include "minirt.h"
# include "libft.h"

int cubes_tests_launcher(void);
int test_cubes_intersect(void);
int test_cubes_ray_misses(void);
int test_cubes_normal_at(void);

#endif
