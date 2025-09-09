/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_tests.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:16:24 by hallison          #+#    #+#             */
/*   Updated: 2025/09/09 18:27:41 by hallison         ###   ########.fr       */
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

#endif
