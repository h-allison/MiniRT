/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_tests.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:16:24 by hallison          #+#    #+#             */
/*   Updated: 2025/09/10 02:28:56 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_TESTS_H
# define SHAPES_TESTS_H

# include "libunit.h"
# include "minirt.h"

int	shapes_tests_launcher(void);
int	test_shape_basic(void);
int	test_shape_transform(void);
int	test_shape_material(void);
int test_shape_ass_material(void);
int test_shape_intersect(void);
int test_shape_translate(void);
int test_shape_normal_translate(void);
int test_shape_normal_transform(void);

#endif
