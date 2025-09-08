/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_tests.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 12:10:04 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/08 15:05:49 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_TESTS_H
# define CAMERA_TESTS_H

# include "libunit.h"
# include "minirt.h"

int	camera_tests_launcher(void);
int	test_camera_floats(void);
int	test_camera_idm(void);
int test_camera_pixel(void);
int test_camera_rayforpixel_1(void);
int test_camera_rayforpixel_2(void);
int test_camera_rayforpixel_3(void);

#endif
