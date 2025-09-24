/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_tests.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hallison <hallison@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 17:16:24 by hallison          #+#    #+#             */
/*   Updated: 2025/09/24 01:21:20 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_TESTS_H
# define TEXTURES_TESTS_H

# include "libunit.h"
# include "minirt.h"

int	textures_tests_launcher(void);
int	test_textures_wrong_header(void);
int	test_textures_size(void);
int	test_textures_read_pixel(void);
int	test_textures_comments(void);
int	test_textures_rgb_span(void);
int	test_textures_rgb_scaling(void);

#endif
