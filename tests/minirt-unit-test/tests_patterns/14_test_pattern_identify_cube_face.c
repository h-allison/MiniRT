/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_test_pattern_identify_cube_face.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:15:50 by mmillhof          #+#    #+#             */
/*   Updated: 2025/09/21 20:28:24 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "patterns_tests.h"

int	test_pattern_identify_cube_face(void)
{
	if (ft_strncmp(face_from_point(point(-1, 0.5, -0.25)), "left", 10))
		return (-1);
	if (ft_strncmp(face_from_point(point(1.1, -0.75, 0.8)), "right", 10))
		return (-1);
	if (ft_strncmp(face_from_point(point(0.1, 0.6, 0.9)), "front", 10))
		return (-1);
	if (ft_strncmp(face_from_point(point(-0.7, 0, -2)), "back", 10))
		return (-1);
	if (ft_strncmp(face_from_point(point(0.5, 1, 0.9)), "up", 10))
		return (-1);
	if (ft_strncmp(face_from_point(point(-0.2, -1.3, 1.1)), "down", 10))
		return (-1);
	return (0);
}
