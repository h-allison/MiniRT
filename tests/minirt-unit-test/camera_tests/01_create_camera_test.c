/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_create_camera_test.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smargine <smargine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:52:32 by smargine          #+#    #+#             */
/*   Updated: 2025/09/08 11:32:09 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "camera_tests.h"
#include "libunit.h"

int	ok_test(void)
{
	int	a;

	a = 4;
	if (a == 4)
		return (0);
	else
		return (-1);
}
