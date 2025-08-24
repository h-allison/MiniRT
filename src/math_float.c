/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_float.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmillhof <mmillhof@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:20:01 by mmillhof          #+#    #+#             */
/*   Updated: 2025/08/24 16:06:51 by mmillhof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	fisequal(float a, float b)
{
	if (fabs(a - b) < EPSILON)
		return (TRUE);
	return (FALSE);
}
