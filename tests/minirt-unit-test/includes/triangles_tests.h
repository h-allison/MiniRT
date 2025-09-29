/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangles_tests.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:16:24 by hallison          #+#    #+#             */
/*   Updated: 2025/09/27 20:56:44 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGLES_TESTS_H
# define TRIANGLES_TESTS_H

# include "libunit.h"
# include "minirt.h"

int	triangles_tests_launcher(void);
int	test_triangles_create(void);
int	test_triangles_normal_at(void);
int	test_triangles_ray_parallel(void);
int	test_triangles_ray_misses_p1_p3(void);
int	test_triangles_ray_misses_p1_p2_p3(void);
int	test_triangles_ray_strikes(void);

#endif
